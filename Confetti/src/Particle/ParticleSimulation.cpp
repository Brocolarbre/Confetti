#include "Confetti/Particle/ParticleSimulation.hpp"

namespace cft
{
	ParticleSimulation::ParticleSimulation() :
		m_particleRegistry(),
		m_randomNumberGenerator(),
		m_particleSystemClips(),
		m_particleSystemInstances(),
		m_particleEffectInstances(),
		m_particleEmitterInstances(),
		m_particlePools()
	{

	}

	ParticleRegistry& ParticleSimulation::getParticleRegistry()
	{
		return m_particleRegistry;
	}

	const std::unordered_map<unsigned int, ParticlePool>& ParticleSimulation::getParticlePools() const
	{
		return m_particlePools;
	}

	void ParticleSimulation::addParticleSystemClip(const ParticleSystemClip& clip)
	{
		m_particleSystemClips.push_back(clip);
	}

	void ParticleSimulation::removeParticleSystemClip(unsigned int index)
	{
		m_particleSystemClips.erase(m_particleSystemClips.begin() + index);
	}

	void ParticleSimulation::setSeed(unsigned int seed)
	{
		m_randomNumberGenerator = RandomNumberGenerator(seed);
	}

	void ParticleSimulation::clear()
	{
		m_particleSystemInstances.clear();
		m_particleEffectInstances.clear();
		m_particleEmitterInstances.clear();
		m_particlePools.clear();
		m_forceFieldSet.clear();
	}

	void ParticleSimulation::start()
	{
		for (unsigned int i = 0; i < m_particleSystemClips.size(); ++i)
		{
			ParticleSystemClip& particleSystemClip = m_particleSystemClips[i];
			m_particleSystemInstances.push_back(ParticleSystemInstance{ particleSystemClip.timeRange, particleSystemClip.forceFields, m_particleRegistry.getParticleSystem(particleSystemClip.systemId).effects }); // Instantiate the particle system by making a copy of the system clip and using the bank system effect clip list
			// EffectClip and EmitterClip instances stored in the class will be read in the update method when creating the corresponding instances
				// The clip variable structure is untouched during simulation, it is only read, only the instances are added and removed
		}
	}

	void ParticleSimulation::update(float elapsedTime, float deltaTime)
	{
		// Particle systems update
		for (unsigned int i = 0; i < m_particleSystemInstances.size();)
		{
			ParticleSystemInstance& particleSystemInstance = m_particleSystemInstances[i];

			float despawnTime = particleSystemInstance.timeRange.spawnTime + particleSystemInstance.timeRange.duration;
			if (despawnTime <= elapsedTime)
			{
				m_particleSystemInstances.erase(m_particleSystemInstances.begin() + i);
			}
			else
			{
				for (unsigned int j = 0; j < particleSystemInstance.effectsToSpawn.size(); ++j)
				{
					const ParticleEffectClip& particleEffectClip = particleSystemInstance.effectsToSpawn[j];
					if (elapsedTime >= particleSystemInstance.timeRange.spawnTime + particleEffectClip.timeRange.spawnTime)
					{
						std::vector<unsigned int> particleEffectInstanceForceFields;
						particleEffectInstanceForceFields.reserve(particleSystemInstance.forceFields.size() + particleEffectClip.forceFields.size());
						particleEffectInstanceForceFields.insert(particleEffectInstanceForceFields.end(), particleSystemInstance.forceFields.begin(), particleSystemInstance.forceFields.end());
						particleEffectInstanceForceFields.insert(particleEffectInstanceForceFields.end(), particleEffectClip.forceFields.begin(), particleEffectClip.forceFields.end());

						m_particleEffectInstances.push_back(ParticleEffectInstance{ particleEffectClip.timeRange, particleEffectInstanceForceFields, m_particleRegistry.getParticleEffect(particleEffectClip.effectId).emitters }); // We give the effect clip force fields to the effect instance, and we also inherit the system force fields to the effect
						m_particleEffectInstances.back().timeRange.spawnTime = elapsedTime;

						particleSystemInstance.effectsToSpawn.erase(particleSystemInstance.effectsToSpawn.begin() + j);
					}
					else
					{
						++j;
					}
				}

				++i;
			}
		}

		// Particle effects update
		for (unsigned int i = 0; i < m_particleEffectInstances.size();)
		{
			ParticleEffectInstance& particleEffectInstance = m_particleEffectInstances[i];

			float despawnTime = particleEffectInstance.timeRange.spawnTime + particleEffectInstance.timeRange.duration;
			if (despawnTime <= elapsedTime)
			{
				m_particleEffectInstances.erase(m_particleEffectInstances.begin() + i);
			}
			else
			{
				for (unsigned int j = 0; j < particleEffectInstance.emittersToSpawn.size(); ++j)
				{
					const ParticleEmitterClip& particleEmitterClip = particleEffectInstance.emittersToSpawn[j];
					if (elapsedTime >= particleEffectInstance.timeRange.spawnTime + particleEmitterClip.timeRange.spawnTime)
					{
						std::vector<unsigned int> particleEmitterInstanceForceFields;
						particleEmitterInstanceForceFields.reserve(particleEffectInstance.forceFields.size() + particleEmitterClip.forceFields.size());
						particleEmitterInstanceForceFields.insert(particleEmitterInstanceForceFields.end(), particleEffectInstance.forceFields.begin(), particleEffectInstance.forceFields.end());
						particleEmitterInstanceForceFields.insert(particleEmitterInstanceForceFields.end(), particleEmitterClip.forceFields.begin(), particleEmitterClip.forceFields.end());

						const ParticleEmitter& particleEmitter = m_particleRegistry.getParticleEmitter(particleEmitterClip.emitterId);

						std::vector<std::reference_wrapper<ForceField>> forceFields;
						forceFields.reserve(particleEmitterInstanceForceFields.size());
						for (unsigned int forceFieldId : particleEmitterInstanceForceFields)
							forceFields.push_back(m_particleRegistry.getForceField(forceFieldId));

						m_particleEmitterInstances.push_back(ParticleEmitterInstance{ particleEffectInstance.timeRange, particleEmitterInstanceForceFields, m_forceFieldSet.createForceFieldSetEntry(forceFields), particleEmitter.group, particleEmitter.spawnRate, 0.0f, particleEmitter.boundaries});
						m_particleEmitterInstances.back().timeRange.spawnTime = elapsedTime;

						m_particlePools[particleEmitter.group].reserve(static_cast<unsigned int>(particleEmitter.spawnRate * particleEmitter.boundaries.maximumLifetime));
						particleEffectInstance.emittersToSpawn.erase(particleEffectInstance.emittersToSpawn.begin() + j);
					}
					else
					{
						++j;
					}
				}

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
				m_particleEmitterInstances.erase(m_particleEmitterInstances.begin() + i);
			}
			else
			{
				float spawnCount = particleEmitterInstance.spawnRate * deltaTime + particleEmitterInstance.accumulator;
				unsigned int roundedSpawnCount = static_cast<unsigned int>(spawnCount);
				particleEmitterInstance.accumulator = spawnCount - static_cast<float>(roundedSpawnCount);

				if (roundedSpawnCount > 0)
				{
					ParticlePool& particlePool = m_particlePools.at(particleEmitterInstance.group);

					for (unsigned int j = 0; j < roundedSpawnCount; ++j)
						particlePool.insert(ParticleGenerator::generate(m_randomNumberGenerator, particleEmitterInstance.boundaries, elapsedTime, particleEmitterInstance.forceFieldSetId));

					m_forceFieldSet.addForceFieldReferenceCount(particleEmitterInstance.forceFieldSetId, roundedSpawnCount);
				}

				++i;
			}
		}

		// Particles update
		for (auto& [_, particlePool] : m_particlePools)
		{
			std::vector<glm::vec3>& position = particlePool.getPosition();
			std::vector<glm::vec3>& velocity = particlePool.getVelocity();
			std::vector<float>& lifetime = particlePool.getLifetime();
			std::vector<float>& spawnTime = particlePool.getSpawnTime();
			std::vector<unsigned int>& forceFieldSetId = particlePool.getForceFieldSetId();

			std::unordered_map<unsigned int, unsigned int> removedParticleCount;

			for (unsigned int i = 0; i < particlePool.getCount();)
			{
				float despawnTime = spawnTime[i] + lifetime[i];
				if (elapsedTime >= despawnTime)
				{
					unsigned int id = forceFieldSetId[i];
					particlePool.remove(i);
					++removedParticleCount[id];
				}
				else
				{
					for (const ForceField& forceField : m_forceFieldSet.getForceFieldIds(forceFieldSetId[i]))
						velocity[i] = forceField.apply(velocity[i], position[i], elapsedTime, deltaTime);

					position[i] += velocity[i] * deltaTime;
					++i;
				}
			}

			for (auto& [id, count] : removedParticleCount)
				m_forceFieldSet.addForceFieldReferenceCount(id, -static_cast<int>(count));
		}
	}
}