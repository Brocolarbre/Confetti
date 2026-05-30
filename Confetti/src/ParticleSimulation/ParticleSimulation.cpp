#include "Confetti/ParticleSimulation/ParticleSimulation.hpp"

namespace cft
{
	ParticleSimulation::ParticleSimulation(ParticleRegistry& particleRegistry, RandomNumberGenerator& randomNumberGenerator) :
		m_particleRegistry(particleRegistry),
		m_randomNumberGenerator(randomNumberGenerator),
		m_particleEffectInstances(),
		m_particleEmitterInstances(),
		m_particlePools(),
		m_particleProperties()
	{

	}

	const std::unordered_map<unsigned int, ParticlePool>& ParticleSimulation::getParticlePools() const
	{
		return m_particlePools;
	}

	void ParticleSimulation::setSeed(unsigned int seed)
	{
		m_randomNumberGenerator = RandomNumberGenerator(seed);
	}

	void ParticleSimulation::addParticleEffect(float elapsedTime, unsigned int id)
	{
		const ParticleEffect& particleEffect = m_particleRegistry.getParticleEffect(id);
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
		m_particleProperties.clear();
	}

	void ParticleSimulation::update(float elapsedTime, float deltaTime)
	{
		// Particle effects update
		for (unsigned int i = 0; i < m_particleEffectInstances.size();)
		{
			ParticleEffectInstance& particleEffectInstance = m_particleEffectInstances[i];

			for (unsigned int j = 0; j < particleEffectInstance.emitters.size(); ++j)
			{
				const ParticleEmitterDescriptor& particleEmitterDescriptor = particleEffectInstance.emitters[j];
				if (elapsedTime >= particleEffectInstance.spawnTime + particleEmitterDescriptor.timeRange.spawnTime)
				{
					const ParticleEmitter& particleEmitter = m_particleRegistry.getParticleEmitter(particleEmitterDescriptor.emitter);

					std::vector<std::unique_ptr<ForceField>> forceFields;
					forceFields.reserve(particleEmitter.forceFields.size());
					for (unsigned int forceField : particleEmitter.forceFields)
						forceFields.push_back(m_particleRegistry.getForceField(forceField).clone());

					ParticleEmitterInstance particleEmitterInstance;

					particleEmitterInstance.particleSpawner = m_particleRegistry.getParticleSpawner(particleEmitter.particleSpawner).clone();
					particleEmitterInstance.spawnPolicy = m_particleRegistry.getSpawnPolicy(particleEmitter.spawnPolicy).clone();
					particleEmitterInstance.emitterBehavior = m_particleRegistry.getParticleEmitterBehavior(particleEmitterDescriptor.emitterBehavior).clone();
					particleEmitterInstance.timeRange = particleEmitterDescriptor.timeRange;
					particleEmitterInstance.timeRange.spawnTime += elapsedTime;
					particleEmitterInstance.pool = particleEmitter.pool;
					particleEmitterInstance.id = m_particleProperties.createEntry(std::move(forceFields), m_particleRegistry.getParticleBehavior(particleEmitter.particleBehavior).clone());
					particleEmitterInstance.position = particleEmitterDescriptor.position;
					particleEmitterInstance.velocity = particleEmitterDescriptor.velocity;

					m_particlePools[particleEmitterInstance.pool].reserve(static_cast<unsigned int>(particleEmitterInstance.spawnPolicy->getSpawnRate() * particleEmitterInstance.particleSpawner->getMaxiumParticleLifetime()));
					particleEffectInstance.emitters[j] = std::move(particleEffectInstance.emitters.back());
					particleEffectInstance.emitters.pop_back();

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

		// Particle emitters update
		for (unsigned int i = 0; i < m_particleEmitterInstances.size();)
		{
			ParticleEmitterInstance& particleEmitterInstance = m_particleEmitterInstances[i];

			float despawnTime = particleEmitterInstance.timeRange.spawnTime + particleEmitterInstance.timeRange.duration;
			if (despawnTime <= elapsedTime)
			{
				m_particleEmitterInstances[i] = std::move(m_particleEmitterInstances.back());
				m_particleEmitterInstances.pop_back();
			}
			else
			{
				particleEmitterInstance.emitterBehavior->update(elapsedTime, deltaTime, ParticleEmitterView{ particleEmitterInstance.position, particleEmitterInstance.velocity });
				particleEmitterInstance.position += particleEmitterInstance.velocity * deltaTime;

				unsigned int particleSpawnCount = particleEmitterInstance.spawnPolicy->getSpawnCount(elapsedTime, deltaTime);
				if (particleSpawnCount > 0)
				{
					std::vector<Particle> particles = particleEmitterInstance.particleSpawner->spawn(particleSpawnCount, elapsedTime, deltaTime, particleEmitterInstance.id);
					
					ParticlePool& particlePool = m_particlePools.at(particleEmitterInstance.pool);
					particlePool.reserve(particleSpawnCount);

					for (Particle& particle : particles)
					{
						particle.position += particleEmitterInstance.position;
						particle.velocity += particleEmitterInstance.velocity;
						particlePool.insert(particle);
					}

					m_particleProperties.addReferenceCount(particleEmitterInstance.id, particleSpawnCount);
				}

				++i;
			}
		}

		// Particles update
		for (auto& [_, particlePool] : m_particlePools)
		{
			std::vector<glm::vec4>& color = particlePool.getColor();
			std::vector<glm::vec3>& position = particlePool.getPosition();
			std::vector<glm::vec3>& velocity = particlePool.getVelocity();
			std::vector<glm::vec2>& scale = particlePool.getScale();
			std::vector<float>& lifetime = particlePool.getLifetime();
			std::vector<float>& spawnTime = particlePool.getSpawnTime();
			std::vector<unsigned int>& id = particlePool.getId();

			std::unordered_map<unsigned int, unsigned int> removedParticleCount;

			for (unsigned int i = 0; i < particlePool.getCount();)
			{
				float despawnTime = spawnTime[i] + lifetime[i];
				if (elapsedTime >= despawnTime)
				{
					unsigned int idCopy = id[i];
					particlePool.remove(i);
					++removedParticleCount[idCopy];
				}
				else
				{
					const ParticlePropertySetEntry& entry = m_particleProperties.getEntry(id[i]);
					
					entry.particleBehavior->update(elapsedTime, deltaTime, ParticleView{ color[i], position[i], velocity[i], scale[i], lifetime[i], spawnTime[i], id[i] });

					const std::vector<std::unique_ptr<ForceField>>& forceFields = entry.forceFields;
					for (const std::unique_ptr<ForceField>& forceField : forceFields)
						velocity[i] += forceField->apply(position[i], elapsedTime, deltaTime);

					position[i] += velocity[i] * deltaTime;
					++i;
				}
			}

			for (auto& [id, count] : removedParticleCount)
				m_particleProperties.addReferenceCount(id, -static_cast<int>(count));
		}
	}
}