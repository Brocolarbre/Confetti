#include "Confetti/ParticleSimulation/ParticleSimulation.hpp"

namespace cft
{
	ParticleSimulation::ParticleSimulation(AssetRegistry& assetRegistry, RandomNumberGenerator& randomNumberGenerator) :
		m_assetRegistry(assetRegistry),
		m_randomNumberGenerator(randomNumberGenerator),
		m_particleEffectInstances(),
		m_particleEmitterInstances(),
		m_particlePools(),
		m_particleRegistry()
	{

	}

	const std::unordered_map<unsigned int, ParticlePool>& ParticleSimulation::getParticlePools() const
	{
		return m_particlePools;
	}

	const ParticleRegistry& ParticleSimulation::getParticleRegistry() const
	{
		return m_particleRegistry;
	}

	void ParticleSimulation::addParticleEffect(float elapsedTime, unsigned int id)
	{
		const ParticleEffect& particleEffect = m_assetRegistry.getParticleEffect(id);
		m_particleEffectInstances.push_back(ParticleEffectInstance{
			elapsedTime,
			particleEffect.emitters
		});
	}

	void ParticleSimulation::clear()
	{
		m_particleEffectInstances.clear();
		m_particleEmitterInstances.clear();
		m_particlePools.clear();
		m_particleRegistry.clear();
	}

	void ParticleSimulation::update(float elapsedTime, float deltaTime)
	{
		// Particle effects update
		for (unsigned int i = 0; i < m_particleEffectInstances.size();)
		{
			ParticleEffectInstance& particleEffectInstance = m_particleEffectInstances[i];

			for (unsigned int j = 0; j < particleEffectInstance.emitters.size();)
			{
				const ParticleEmitterDescriptor& particleEmitterDescriptor = particleEffectInstance.emitters[j];
				if (elapsedTime >= particleEffectInstance.spawnTime + particleEmitterDescriptor.timeRange.spawnTime)
				{
					const ParticleEmitter& particleEmitter = m_assetRegistry.getParticleEmitter(particleEmitterDescriptor.emitter);

					std::vector<std::unique_ptr<ForceField>> forceFields;
					forceFields.reserve(particleEmitter.forceFields.size());
					for (unsigned int forceField : particleEmitter.forceFields)
						forceFields.push_back(m_assetRegistry.getForceField(forceField).clone());

					std::vector<std::unique_ptr<MotionBehavior>> motionBehaviors;
					motionBehaviors.reserve(particleEmitter.motionBehaviors.size());
					for (unsigned int motionBehavior : particleEmitter.motionBehaviors)
						motionBehaviors.push_back(m_assetRegistry.getMotionBehavior(motionBehavior).clone());

					std::vector<std::unique_ptr<ParticleBehavior>> particleBehaviors;
					particleBehaviors.reserve(particleEmitter.particleBehaviors.size());
					for (unsigned int particleBehavior : particleEmitter.particleBehaviors)
						particleBehaviors.push_back(m_assetRegistry.getParticleBehavior(particleBehavior).clone());

					ParticleEmitterInstance particleEmitterInstance;

					particleEmitterInstance.timeRange = particleEmitterDescriptor.timeRange;
					particleEmitterInstance.timeRange.spawnTime += elapsedTime;
					particleEmitterInstance.transform = particleEmitterDescriptor.transform;
					particleEmitterInstance.particleRegistryId = m_particleRegistry.createEntry(particleEmitter.pool, 0, particleEmitter.spawnTrigger, particleEmitter.renderDescriptor, std::move(forceFields), std::move(motionBehaviors), std::move(particleBehaviors));
					particleEmitterInstance.particleSpawner = m_assetRegistry.getParticleSpawner(particleEmitter.particleSpawner).clone();
					particleEmitterInstance.spawnPolicy = m_assetRegistry.getSpawnPolicy(particleEmitter.spawnPolicy).clone();
					
					particleEmitterInstance.inheritedForceFields.reserve(particleEmitterDescriptor.forceFields.size());
					for (unsigned int forceField : particleEmitterDescriptor.forceFields)
						particleEmitterInstance.inheritedForceFields.push_back(m_assetRegistry.getForceField(forceField).clone());

					particleEmitterInstance.inheritedMotionBehaviors.reserve(particleEmitterDescriptor.motionBehaviors.size());
					for (unsigned int motionBehavior : particleEmitterDescriptor.motionBehaviors)
						particleEmitterInstance.inheritedMotionBehaviors.push_back(m_assetRegistry.getMotionBehavior(motionBehavior).clone());

					m_particlePools[particleEmitter.pool].reserve(static_cast<unsigned int>(particleEmitterInstance.spawnPolicy->getSpawnRate() * particleEmitterInstance.particleSpawner->getMaxiumParticleLifetime()));
					particleEffectInstance.emitters[j] = std::move(particleEffectInstance.emitters.back());
					particleEffectInstance.emitters.pop_back();

					m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, 1);
					m_particleEmitterInstances.push_back(std::move(particleEmitterInstance));
				}
				else
				{
					++j;
				}
			}

			if (particleEffectInstance.emitters.empty())
			{
				m_particleEffectInstances[i] = std::move(m_particleEffectInstances.back());
				m_particleEffectInstances.pop_back();
			}
			else
			{
				++i;
			}
		}

		std::vector<ParticleEmitterInstance> pendingParticleEmitterInstances;

		// Particle emitters update
		for (unsigned int i = 0; i < m_particleEmitterInstances.size();)
		{
			ParticleEmitterInstance& particleEmitterInstance = m_particleEmitterInstances[i];

			float despawnTime = particleEmitterInstance.timeRange.spawnTime + particleEmitterInstance.timeRange.duration;
			if (elapsedTime >= despawnTime)
			{
				m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, -1);
				m_particleEmitterInstances[i] = std::move(m_particleEmitterInstances.back());
				m_particleEmitterInstances.pop_back();
			}
			else
			{
				for (const std::unique_ptr<ForceField>& forceField : particleEmitterInstance.inheritedForceFields)
					particleEmitterInstance.transform.velocity += forceField->apply(elapsedTime, particleEmitterInstance.transform) * deltaTime;

				for (const std::unique_ptr<MotionBehavior>& motionBehavior : particleEmitterInstance.inheritedMotionBehaviors)
					motionBehavior->update(elapsedTime, deltaTime, particleEmitterInstance.transform);
				
				particleEmitterInstance.transform.position += particleEmitterInstance.transform.velocity * deltaTime;

				unsigned int particleSpawnCount = particleEmitterInstance.spawnPolicy->getSpawnCount(elapsedTime, deltaTime);
				if (particleSpawnCount > 0)
				{
					std::vector<Particle> particles = particleEmitterInstance.particleSpawner->spawn(particleSpawnCount, elapsedTime, deltaTime, particleEmitterInstance.particleRegistryId);
					
					const ParticleRegistryEntry& particleRegistryEntry = m_particleRegistry.getEntry(particleEmitterInstance.particleRegistryId);
					ParticlePool& particlePool = m_particlePools.at(particleRegistryEntry.pool);
					particlePool.reserve(particleSpawnCount);

					// -----
					bool spawnTrigger = false;
					ParticleEmitterDescriptor spawnEmitterDescriptor;
					if (particleRegistryEntry.spawnTrigger.has_value())
					{
						const SpawnTrigger& spawnTriggerValue = particleRegistryEntry.spawnTrigger.value();
						spawnTrigger = particleRegistryEntry.recursionDepth < spawnTriggerValue.maximumRecursionDepth && spawnTriggerValue.spawnEmitter.has_value();
						spawnEmitterDescriptor = spawnTriggerValue.spawnEmitter.value();
					}
					// -----

					for (Particle& particle : particles)
					{
						particle.position += particleEmitterInstance.transform.position;
						particle.velocity += particleEmitterInstance.transform.velocity;
						particlePool.insert(particle);

						// -----
						if (spawnTrigger)
						{
							const ParticleEmitter& particleEmitter = m_assetRegistry.getParticleEmitter(spawnEmitterDescriptor.emitter);

							std::vector<std::unique_ptr<ForceField>> forceFields;
							forceFields.reserve(particleEmitter.forceFields.size());
							for (unsigned int forceField : particleEmitter.forceFields)
								forceFields.push_back(m_assetRegistry.getForceField(forceField).clone());

							std::vector<std::unique_ptr<MotionBehavior>> motionBehaviors;
							motionBehaviors.reserve(particleEmitter.motionBehaviors.size());
							for (unsigned int motionBehavior : particleEmitter.motionBehaviors)
								motionBehaviors.push_back(m_assetRegistry.getMotionBehavior(motionBehavior).clone());

							std::vector<std::unique_ptr<ParticleBehavior>> particleBehaviors;
							particleBehaviors.reserve(particleEmitter.particleBehaviors.size());
							for (unsigned int particleBehavior : particleEmitter.particleBehaviors)
								particleBehaviors.push_back(m_assetRegistry.getParticleBehavior(particleBehavior).clone());

							ParticleEmitterInstance spawnParticleEmitterInstance;

							spawnParticleEmitterInstance.timeRange = spawnEmitterDescriptor.timeRange;
							spawnParticleEmitterInstance.timeRange.spawnTime += elapsedTime;
							spawnParticleEmitterInstance.transform = Transform{ particle.position + spawnEmitterDescriptor.transform.position, particle.velocity + spawnEmitterDescriptor.transform.velocity, particle.rotation + spawnEmitterDescriptor.transform.rotation, particle.angularVelocity + spawnEmitterDescriptor.transform.angularVelocity };
							spawnParticleEmitterInstance.particleRegistryId = m_particleRegistry.createEntry(particleEmitter.pool, particleRegistryEntry.recursionDepth + 1, particleEmitter.spawnTrigger, particleEmitter.renderDescriptor, std::move(forceFields), std::move(motionBehaviors), std::move(particleBehaviors));
							spawnParticleEmitterInstance.particleSpawner = m_assetRegistry.getParticleSpawner(particleEmitter.particleSpawner).clone();
							spawnParticleEmitterInstance.spawnPolicy = m_assetRegistry.getSpawnPolicy(particleEmitter.spawnPolicy).clone();

							spawnParticleEmitterInstance.inheritedForceFields.reserve(spawnEmitterDescriptor.forceFields.size());
							for (unsigned int forceField : spawnEmitterDescriptor.forceFields)
								spawnParticleEmitterInstance.inheritedForceFields.push_back(m_assetRegistry.getForceField(forceField).clone());

							spawnParticleEmitterInstance.inheritedMotionBehaviors.reserve(spawnEmitterDescriptor.motionBehaviors.size());
							for (unsigned int motionBehavior : spawnEmitterDescriptor.motionBehaviors)
								spawnParticleEmitterInstance.inheritedMotionBehaviors.push_back(m_assetRegistry.getMotionBehavior(motionBehavior).clone());

							m_particlePools[particleEmitter.pool].reserve(static_cast<unsigned int>(spawnParticleEmitterInstance.spawnPolicy->getSpawnRate() * spawnParticleEmitterInstance.particleSpawner->getMaxiumParticleLifetime()));

							//m_particleRegistry.addReferenceCount(spawnParticleEmitterInstance.particleRegistryId, 1);
							//m_particleEmitterInstances.push_back(std::move(spawnParticleEmitterInstance));
							pendingParticleEmitterInstances.push_back(std::move(spawnParticleEmitterInstance));
						}
						// -----
					}

					m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, particleSpawnCount);
				}

				++i;
			}
		}

		for (ParticleEmitterInstance& particleEmitterInstance : pendingParticleEmitterInstances)
		{
			m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, 1);
			m_particleEmitterInstances.push_back(std::move(particleEmitterInstance));
		}

		// Particles update
		for (auto& [poolId, particlePool] : m_particlePools)
		{
			std::vector<glm::vec4>& color = particlePool.getColor();
			std::vector<glm::vec4>& initialColor = particlePool.getInitialColor();
			std::vector<glm::vec3>& position = particlePool.getPosition();
			std::vector<glm::vec3>& velocity = particlePool.getVelocity();
			std::vector<glm::quat>& rotation = particlePool.getRotation();
			std::vector<glm::vec3>& angularVelocity = particlePool.getAngularVelocity();
			std::vector<glm::vec3>& scale = particlePool.getScale();
			std::vector<glm::vec3>& initialScale = particlePool.getInitialScale();
			std::vector<float>& phase = particlePool.getPhase();
			std::vector<float>& lifetime = particlePool.getLifetime();
			std::vector<float>& spawnTime = particlePool.getSpawnTime();
			std::vector<unsigned int>& id = particlePool.getId();

			std::unordered_map<unsigned int, unsigned int> removedParticleCount;

			for (unsigned int i = 0; i < particlePool.getCount();)
			{
				float despawnTime = spawnTime[i] + lifetime[i];
				if (elapsedTime >= despawnTime)
				{
					++removedParticleCount[id[i]];
					particlePool.remove(i);
				}
				else
				{
					const ParticleRegistryEntry& entry = m_particleRegistry.getEntry(id[i]);
					
					Transform transform{ position[i], velocity[i], rotation[i], angularVelocity[i] };
					for (const std::unique_ptr<ForceField>& forceField : entry.forceFields)
						transform.velocity += forceField->apply(elapsedTime, transform) * deltaTime;

					for (const std::unique_ptr<MotionBehavior>& motionBehavior : entry.motionBehaviors)
						motionBehavior->update(elapsedTime, deltaTime, transform);

					position[i] = transform.position;
					velocity[i] = transform.velocity;

					float progress = (elapsedTime - spawnTime[i]) / lifetime[i];

					for (const std::unique_ptr<ParticleBehavior>& particleBehavior : entry.particleBehaviors)
						particleBehavior->update(elapsedTime, deltaTime, progress, ParticleView{ color[i], initialColor[i], position[i], velocity[i], rotation[i], angularVelocity[i], scale[i], initialScale[i], phase[i], lifetime[i], spawnTime[i], id[i]});

					rotation[i] = glm::normalize(glm::quat(1.0f, 0.5f * angularVelocity[i] * deltaTime) * rotation[i]);
					position[i] += velocity[i] * deltaTime;
					++i;
				}
			}

			for (auto& [id, count] : removedParticleCount)
				m_particleRegistry.addReferenceCount(id, -static_cast<int>(count));
		}
	}
}