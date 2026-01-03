#include "ConfettiEngine/Particle/ParticleSimulation.hpp"

namespace cft
{
	ParticleSimulation::ParticleSimulation() :
		m_particleRegistry(),
		m_randomNumberGenerator(),
		m_particlePools(),
		m_particleSystems(),
		m_particleEffects(),
		m_particleEmitters()
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

	void ParticleSimulation::setSeed(unsigned int seed)
	{
		m_randomNumberGenerator = RandomNumberGenerator(seed);
	}

	void ParticleSimulation::addParticleSystem(unsigned int id)
	{
		m_particleSystems.push_back(m_particleRegistry.getParticleSystem(id));
	}

	void ParticleSimulation::clear()
	{
		m_particleSystems.clear();
		m_particleEffects.clear();
		m_particleEmitters.clear();
		m_particlePools.clear();
	}

	void ParticleSimulation::update(float elapsedTime, float deltaTime)
	{
		// System update
		for (unsigned int i = 0; i < m_particleSystems.size();)
		{
			ParticleSystem& system = m_particleSystems[i];

			float despawnTime = system.spawnTime + system.lifetime;
			if (despawnTime <= elapsedTime)
			{
				m_particleSystems.erase(m_particleSystems.begin() + i);
			}
			else
			{
				std::vector<unsigned int>& effects = system.effects;
				for (unsigned int j = 0; j < effects.size();)
				{
					const ParticleEffect& effect = m_particleRegistry.getParticleEffect(effects[j]);
					if (system.spawnTime + effect.spawnTime <= elapsedTime)
					{
						m_particleEffects.push_back(effect);
						m_particleEffects.back().spawnTime = elapsedTime;

						effects.erase(effects.begin() + j);
					}
					else
					{
						++j;
					}
				}

				++i;
			}
		}

		// Effect update
		for (unsigned int i = 0; i < m_particleEffects.size();)
		{
			ParticleEffect& effect = m_particleEffects[i];

			float despawnTime = effect.spawnTime + effect.lifetime;
			if (despawnTime <= elapsedTime)
			{
				m_particleEffects.erase(m_particleEffects.begin() + i);
			}
			else
			{
				std::vector<unsigned int>& emitters = effect.emitters;
				for (unsigned int j = 0; j < emitters.size();)
				{
					const ParticleEmitter& emitter = m_particleRegistry.getParticleEmitter(emitters[j]);
					if (effect.spawnTime + emitter.spawnTime <= elapsedTime)
					{
						m_particleEmitters.push_back(emitter);
						m_particleEmitters.back().spawnTime = elapsedTime;

						m_particlePools[emitter.type].reserve(static_cast<unsigned int>(emitter.spawnRate * emitter.boundaries.maximumLifetime));
						emitters.erase(emitters.begin() + j);
					}
					else
					{
						++j;
					}
				}

				++i;
			}
		}

		// Emitter update
		for (unsigned int i = 0; i < m_particleEmitters.size();)
		{
			ParticleEmitter& emitter = m_particleEmitters[i];

			float despawnTime = emitter.spawnTime + emitter.lifetime;
			if (despawnTime <= elapsedTime)
			{
				m_particleEmitters.erase(m_particleEmitters.begin() + i);
			}
			else
			{
				float spawnCount = emitter.spawnRate * deltaTime + emitter.accumulator;
				unsigned int roundedSpawnCount = static_cast<unsigned int>(spawnCount);
				emitter.accumulator = spawnCount - static_cast<float>(roundedSpawnCount);

				if (roundedSpawnCount > 0)
				{
					ParticlePool& pool = m_particlePools.at(emitter.type);

					for (unsigned int j = 0; j < roundedSpawnCount; ++j)
						pool.insert(ParticleGenerator::generate(m_randomNumberGenerator, emitter.boundaries, elapsedTime, emitter.type, emitter.instance));
				}

				++i;
			}
		}

		// Particle update
		for (auto& [_, pool] : m_particlePools)
		{
			std::vector<glm::vec3>& position = pool.getPosition();
			std::vector<glm::vec3>& velocity = pool.getVelocity();
			std::vector<float>& lifetime = pool.getLifetime();
			std::vector<float>& spawnTime = pool.getSpawnTime();
			std::vector<unsigned int>& emitterType = pool.getEmitterType();
			std::vector<unsigned int>& emitterInstance = pool.getEmitterInstance();
			unsigned int particleCount = pool.getCount();

			for (unsigned int i = 0; i < pool.getCount();)
			{
				float despawnTime = spawnTime[i] + lifetime[i];
				if (despawnTime <= elapsedTime)
				{
					pool.remove(i);
				}
				else
				{
					const ParticleEntry& emitter = m_particleRegistry.getParticleEmitterEntry(emitterType[i], emitterInstance[i]);
					const ParticleEntry& effect = m_particleRegistry.getParticleEffectEntry(emitter.parentType, emitter.parentInstance);
					const std::vector<unsigned int>& systemForceFields = m_particleRegistry.getParticleSystemEntry(effect.parentType, effect.parentInstance);
					const std::vector<unsigned int>& effectForceFields = effect.forceFields;
					const std::vector<unsigned int>& emitterForceFields = emitter.forceFields;

					auto applyForceFields = [&](const std::vector<unsigned int>& forceFields)
						{
							for (unsigned int forceFieldId : forceFields)
							{
								const ForceField& forceField = m_particleRegistry.getForceField(forceFieldId);
								velocity[i] = forceField.apply(velocity[i], elapsedTime, deltaTime);
							}
						};

					applyForceFields(systemForceFields);
					applyForceFields(effectForceFields);
					applyForceFields(emitterForceFields);

					position[i] += velocity[i] * deltaTime;
					++i;
				}
			}
		}
	}
}