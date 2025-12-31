#include "ConfettiEngine/Particle/ParticleEffectPool.hpp"
#include "ConfettiEngine/Particle/ParticleOrchestrator.hpp"

namespace cft
{
	ParticleEffectPool::ParticleEffectPool(ParticleOrchestrator& particleOrchestrator) :
		m_effects(),
		m_capacity(0),
		m_count(0),
		m_particleOrchestrator(particleOrchestrator)
	{

	}

	unsigned int ParticleEffectPool::getCapacity() const
	{
		return m_capacity;
	}

	unsigned int ParticleEffectPool::getCount() const
	{
		return m_count;
	}

	void ParticleEffectPool::createParticleEffect(const ParticleEffect& effect)
	{
		unsigned int newIndex = m_count++;
		m_effects[newIndex] = effect;
	}

	void ParticleEffectPool::destroyParticleEffect(unsigned int index)
	{
		unsigned int lastIndex = --m_count;
		m_effects[index] = m_effects[lastIndex];
	}

	void ParticleEffectPool::resize(unsigned int capacity)
	{
		m_effects.resize(capacity);
		m_capacity = capacity;
		m_count = glm::min(m_count, m_capacity);
	}

	void ParticleEffectPool::update(float elapsedTime, float deltaTime)
	{
		for (unsigned int i = 0; i < m_count;)
		{
			float despawnTime = m_effects[i].spawnTime + m_effects[i].lifetime;
			if (despawnTime <= elapsedTime)
			{
				destroyParticleEffect(i);
			}
			else
			{
				std::vector<unsigned int>& emitters = m_effects[i].emitters;
				for (unsigned int j = 0; j < emitters.size();)
				{
					ParticleEmitter emitter = m_particleOrchestrator.getParticleEmitter(emitters[j]);
					if (m_effects[i].spawnTime + emitter.spawnTime <= elapsedTime)
					{
						emitter.spawnTime = elapsedTime;
						m_particleOrchestrator.createParticleEmitter(emitter);
						emitters[j] = emitters[emitters.size() - 1];
						emitters.erase(emitters.end() - 1);
					}
					else
					{
						++j;
					}
				}

				++i;
			}
		}
	}
}