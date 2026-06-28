#include "Confetti/ParticleSimulation/ParticleSimulation.hpp"

#include <unordered_set>

namespace cft
{
	ParticleEmitterInstance ParticleSimulation::createParticleEmitter(const ParticleEmitterDescriptor& descriptor, const Transform& parentTransform, unsigned int recursionDepth, float elapsedTime)
	{
		const ParticleEmitter& particleEmitter = m_assetRegistry.getParticleEmitter(descriptor.emitter);

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

		particleEmitterInstance.timeRange = descriptor.timeRange;
		particleEmitterInstance.timeRange.spawnTime += elapsedTime;
		particleEmitterInstance.transform = Transform{ parentTransform.position + descriptor.transform.position, parentTransform.velocity + descriptor.transform.velocity, parentTransform.rotation + descriptor.transform.rotation, parentTransform.angularVelocity + descriptor.transform.angularVelocity };
		particleEmitterInstance.particleRegistryId = m_particleRegistry.createEntry(particleEmitter.pool, recursionDepth, particleEmitter.spawnTrigger, particleEmitter.renderDescriptor, std::move(forceFields), std::move(motionBehaviors), std::move(particleBehaviors));
		particleEmitterInstance.trailRegistryId = particleEmitter.trailConfiguration.has_value() ? std::make_optional<unsigned int>(m_trailRegistry.createEntry(particleEmitter.trailConfiguration.value())) : std::nullopt;
		particleEmitterInstance.particleSpawner = m_assetRegistry.getParticleSpawner(particleEmitter.particleSpawner).clone();
		particleEmitterInstance.spawnPolicy = m_assetRegistry.getSpawnPolicy(particleEmitter.spawnPolicy).clone();

		particleEmitterInstance.inheritedForceFields.reserve(descriptor.forceFields.size());
		for (unsigned int forceField : descriptor.forceFields)
			particleEmitterInstance.inheritedForceFields.push_back(m_assetRegistry.getForceField(forceField).clone());

		particleEmitterInstance.inheritedMotionBehaviors.reserve(descriptor.motionBehaviors.size());
		for (unsigned int motionBehavior : descriptor.motionBehaviors)
			particleEmitterInstance.inheritedMotionBehaviors.push_back(m_assetRegistry.getMotionBehavior(motionBehavior).clone());

		unsigned int maximumParticleCount = static_cast<unsigned int>(particleEmitterInstance.spawnPolicy->getSpawnRate() * particleEmitterInstance.particleSpawner->getMaxiumParticleLifetime());
		m_particlePools[particleEmitter.pool].reserve(maximumParticleCount);
		m_trailPools[particleEmitter.pool].reserve(maximumParticleCount);
		
		return particleEmitterInstance;
	}

	ParticleSimulation::ParticleSimulation(AssetRegistry& assetRegistry, RandomNumberGenerator& randomNumberGenerator) :
		m_assetRegistry(assetRegistry),
		m_randomNumberGenerator(randomNumberGenerator),
		m_particleEffectInstances(),
		m_particleEmitterInstances(),
		m_particlePools(),
		m_trailPools(),
		m_particleRegistry(),
		m_trailRegistry()
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
					ParticleEmitterInstance particleEmitterInstance = createParticleEmitter(particleEmitterDescriptor, Transform{}, 0, elapsedTime);

					m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, 1);
					//
					if (particleEmitterInstance.trailRegistryId.has_value())
						m_trailRegistry.addReferenceCount(particleEmitterInstance.trailRegistryId.value(), 1);
					//
					m_particleEmitterInstances.push_back(std::move(particleEmitterInstance));

					particleEffectInstance.emitters[j] = std::move(particleEffectInstance.emitters.back());
					particleEffectInstance.emitters.pop_back();
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
				//
				if (particleEmitterInstance.trailRegistryId.has_value())
					m_trailRegistry.addReferenceCount(particleEmitterInstance.trailRegistryId.value(), -1);
				//
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
					// Create particle id
					std::vector<Particle> particles = particleEmitterInstance.particleSpawner->spawn(particleSpawnCount, elapsedTime, deltaTime, particleEmitterInstance.particleRegistryId);
					
					const ParticleRegistryEntry& particleRegistryEntry = m_particleRegistry.getEntry(particleEmitterInstance.particleRegistryId);
					ParticlePool& particlePool = m_particlePools.at(particleRegistryEntry.pool);
					particlePool.reserve(particleSpawnCount);

					bool spawnSpawnTrigger = false;
					ParticleEmitterDescriptor spawnParticleEmitterDescriptor;
					if (particleRegistryEntry.spawnTrigger.has_value())
					{
						const SpawnTrigger& spawnTriggerValue = particleRegistryEntry.spawnTrigger.value();
						spawnSpawnTrigger = particleRegistryEntry.recursionDepth < spawnTriggerValue.maximumRecursionDepth && spawnTriggerValue.spawnEmitter.has_value();
						if (spawnSpawnTrigger)
							spawnParticleEmitterDescriptor = spawnTriggerValue.spawnEmitter.value();
					}

					bool spawnTrails = particleEmitterInstance.trailRegistryId.has_value();
					std::optional<TrailPool*> trailPool;
					if (spawnTrails)
						trailPool = &m_trailPools.at(particleRegistryEntry.pool);

					for (Particle& particle : particles)
					{
						particle.position += particleEmitterInstance.transform.position;
						particle.velocity += particleEmitterInstance.transform.velocity;
						particlePool.insert(particle);

						if (spawnTrails)
							trailPool.value()->insert(Trail{ particleEmitterInstance.trailRegistryId.value(), particle.id, -1.0f, {} });

						if (spawnSpawnTrigger)
						{
							ParticleEmitterInstance spawnParticleEmitterInstance = createParticleEmitter(spawnParticleEmitterDescriptor, Transform{ particle.position, particle.velocity, particle.rotation, particle.angularVelocity }, particleRegistryEntry.recursionDepth + 1, elapsedTime);
							pendingParticleEmitterInstances.push_back(std::move(spawnParticleEmitterInstance));
						}
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

		std::unordered_set<unsigned int> triggeredPeriodicSpawnTriggers;

		for (auto& [id, entry] : m_particleRegistry.getEntries())
		{
			if (entry.spawnTrigger.has_value() && entry.spawnTrigger.value().periodicEmitter.has_value())
			{
				SpawnTrigger& spawnTrigger = entry.spawnTrigger.value();
				if (spawnTrigger.periodicEmitter.has_value())
				{
					PeriodicSpawnTrigger& periodicSpawnTrigger = spawnTrigger.periodicEmitter.value();
					entry.periodicTriggerAccumulator += deltaTime;

					if (entry.recursionDepth < spawnTrigger.maximumRecursionDepth && entry.periodicTriggerAccumulator >= periodicSpawnTrigger.interval)
					{
						triggeredPeriodicSpawnTriggers.insert(id);
						entry.periodicTriggerAccumulator -= periodicSpawnTrigger.interval;
					}
				}
			}
		}

		// Particles update
		for (auto& [poolId, particlePool] : m_particlePools)
		{
			// const
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
			std::vector<unsigned int>& particleRegistryId = particlePool.getParticleRegistryId();

			std::unordered_map<unsigned int, unsigned int> removedParticleCount;

			for (unsigned int i = 0; i < particlePool.getCount();)
			{
				ParticleRegistryEntry& entry = m_particleRegistry.getEntry(particleRegistryId[i]);

				float despawnTime = spawnTime[i] + lifetime[i];
				if (elapsedTime >= despawnTime)
				{				
					if (entry.spawnTrigger.has_value())
					{
						const SpawnTrigger& spawnTriggerValue = entry.spawnTrigger.value();
						if (entry.recursionDepth < spawnTriggerValue.maximumRecursionDepth && spawnTriggerValue.deathEmitter.has_value())
						{
							ParticleEmitterInstance deathParticleEmitterInstance = createParticleEmitter(spawnTriggerValue.deathEmitter.value(), Transform{ position[i], velocity[i], rotation[i], angularVelocity[i] }, entry.recursionDepth + 1, elapsedTime);
							m_particleRegistry.addReferenceCount(deathParticleEmitterInstance.particleRegistryId, 1);
							m_particleEmitterInstances.push_back(std::move(deathParticleEmitterInstance));
						}
					}

					++removedParticleCount[particleRegistryId[i]];
					particlePool.remove(i);
				}
				else
				{
					if (triggeredPeriodicSpawnTriggers.find(particleRegistryId[i]) != triggeredPeriodicSpawnTriggers.end())
					{
						ParticleEmitterInstance periodicParticleEmitterInstance = createParticleEmitter(entry.spawnTrigger.value().periodicEmitter.value().emitter, Transform{position[i], velocity[i], rotation[i], angularVelocity[i]}, entry.recursionDepth + 1, elapsedTime);
						m_particleRegistry.addReferenceCount(periodicParticleEmitterInstance.particleRegistryId, 1);
						m_particleEmitterInstances.push_back(std::move(periodicParticleEmitterInstance));
					}

					Transform transform{ position[i], velocity[i], rotation[i], angularVelocity[i] };
					for (const std::unique_ptr<ForceField>& forceField : entry.forceFields)
						transform.velocity += forceField->apply(elapsedTime, transform) * deltaTime;

					for (const std::unique_ptr<MotionBehavior>& motionBehavior : entry.motionBehaviors)
						motionBehavior->update(elapsedTime, deltaTime, transform);

					position[i] = transform.position;
					velocity[i] = transform.velocity;

					float progress = (elapsedTime - spawnTime[i]) / lifetime[i];

					for (const std::unique_ptr<ParticleBehavior>& particleBehavior : entry.particleBehaviors)
						particleBehavior->update(elapsedTime, deltaTime, progress, ParticleView{ color[i], initialColor[i], position[i], velocity[i], rotation[i], angularVelocity[i], scale[i], initialScale[i], phase[i], lifetime[i], spawnTime[i], particleRegistryId[i], id[i] });

					rotation[i] = glm::normalize(glm::quat(1.0f, 0.5f * angularVelocity[i] * deltaTime) * rotation[i]);
					position[i] += velocity[i] * deltaTime;
					++i;
				}
			}

			for (auto& [particleRegistry, count] : removedParticleCount)
				m_particleRegistry.addReferenceCount(particleRegistry, -static_cast<int>(count));
		}

		// Trails update
		for (auto& [poolId, trailPool] : m_trailPools)
		{
			// const
			std::vector<unsigned int>& trailRegistryId = trailPool.getTrailRegistryId();
			std::vector<unsigned int>& particleId = trailPool.getParticleId();
			std::vector<float>& particleDeathTime = trailPool.getParticleDeathTime();
			std::vector<std::deque<TrailPoint>>& trailPoints = trailPool.getTrailPoints();

			std::unordered_map<unsigned int, unsigned int> removedTrailCount;

			for (unsigned int i = 0; i < trailPool.getCount();)
			{
				TrailRegistryEntry& trailRegistryEntry = m_trailRegistry.getEntry(trailRegistryId[i]);

				if (particleDeathTime[i] < 0.0f)
				{
					const ParticlePool& particlePool = m_particlePools.at(poolId);

					std::optional<unsigned int> ownerParticleIndex = particlePool.getIndex(particleId[i]);
					if (!ownerParticleIndex.has_value())
					{
						particleDeathTime[i] = elapsedTime;
					}
					else
					{
						glm::vec3 particlePosition = particlePool.getPosition()[ownerParticleIndex.value()];
						if (trailPoints[i].empty() || glm::distance(particlePosition, trailPoints[i].back().position) > trailRegistryEntry.trailConfiguration.minimumSpawnDistance || (trailRegistryEntry.trailConfiguration.maximumSpawnTime.has_value() && elapsedTime - trailPoints[i].back().spawnTime > trailRegistryEntry.trailConfiguration.maximumSpawnTime.value()))
						{
							trailPoints[i].push_back(TrailPoint{ glm::vec4(0.0f), particlePosition, 0.0f, elapsedTime });

							if (trailRegistryEntry.trailConfiguration.maximumSegmentCount.value() > trailPoints[i].size())
							{
								while (trailPoints[i].size() > trailRegistryEntry.trailConfiguration.maximumSegmentCount.value())
									trailPoints[i].pop_front();
							}
						}
					}
				}

				if (particleDeathTime[i] >= 0.0f && elapsedTime >= trailRegistryEntry.trailConfiguration.presistenceLifetime + particleDeathTime[i])
				{
					++removedTrailCount[trailRegistryId[i]];
					trailPool.remove(i);
				}
				else
				{
					std::deque<TrailPoint>& trail = trailPoints[i];
					unsigned int trailSize = static_cast<unsigned int>(trail.size());

					for (unsigned int pointIndex = 0; pointIndex < trail.size(); ++pointIndex)
					{
						float t = static_cast<float>(pointIndex) / static_cast<float>(trailSize - 1);

						switch (trailRegistryEntry.trailConfiguration.thicknessEvolution)
						{
						case TrailThicknessEvolution::Constant: trail[pointIndex].thickness = trailRegistryEntry.trailConfiguration.thickness; break;
						case TrailThicknessEvolution::LinearDecreasing: trail[pointIndex].thickness = (1.0f - t) * trailRegistryEntry.trailConfiguration.thickness; break;
						case TrailThicknessEvolution::QuadraticDecreasing: trail[pointIndex].thickness = (1.0f - t) * (1.0f - t) * trailRegistryEntry.trailConfiguration.thickness; break;
						case TrailThicknessEvolution::LinearIncreasing: trail[pointIndex].thickness = t * trailRegistryEntry.trailConfiguration.thickness; break;
						case TrailThicknessEvolution::QuadraticIncreasing: trail[pointIndex].thickness = t * t * trailRegistryEntry.trailConfiguration.thickness; break;
						}

						unsigned int gradientSize = static_cast<unsigned int>(trailRegistryEntry.trailConfiguration.colorGradient.size());
						float integralPart;
						float colorT = std::modf(t * static_cast<float>(gradientSize - 1), &integralPart);
						
						unsigned int colorIndexA = static_cast<unsigned int>(integralPart);
						unsigned int colorIndexB = glm::min(colorIndexA + 1, gradientSize - 1);
						trail[pointIndex].color = (1.0f - colorT) * trailRegistryEntry.trailConfiguration.colorGradient[colorIndexA] + colorT * trailRegistryEntry.trailConfiguration.colorGradient[colorIndexB];

						if (trailRegistryEntry.trailConfiguration.lifetimeFade.has_value())
						{
							float start = trailRegistryEntry.trailConfiguration.lifetimeFade.value().start;
							float end = trailRegistryEntry.trailConfiguration.lifetimeFade.value().end;
	
							float age = elapsedTime - trail[pointIndex].spawnTime;
							float trailFadeT = end > start ? (glm::clamp(age, start, end) - start) / (end - start) : 1.0f;

							trail[pointIndex].color.a *= (1.0f - trailFadeT) * 1.0f + trailFadeT * 0.0f;
						}
					}

					if (trailRegistryEntry.trailConfiguration.pointLifetime.has_value())
					{
						while (!trail.empty() && elapsedTime >= trail.front().spawnTime + trailRegistryEntry.trailConfiguration.pointLifetime.value())
							trail.pop_front();
					}

					++i;
				}
			}

			for (auto& [trailRegistry, count] : removedTrailCount)
				m_trailRegistry.addReferenceCount(trailRegistry, -static_cast<int>(count));
		}
	}
}