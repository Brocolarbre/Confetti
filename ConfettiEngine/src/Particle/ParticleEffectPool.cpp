#include "ConfettiEngine/Particle/ParticleEffectPool.hpp"
#include "ConfettiEngine/Particle/ParticleSystem.hpp"

namespace cft
{
	ParticleEffectPool::ParticleEffectPool(ParticleSystem& particleSystem) :
		m_effects(),
		m_capacity(0),
		m_count(0),
		m_particleSystem(particleSystem)
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
	}

	void ParticleEffectPool::update(float elapsedTime, float deltaTime)
	{
		unsigned int i = 0;
		while (i < m_count)
		{
			float despawnTime = m_effects[i].spawnTime + m_effects[i].lifetime;
			if (despawnTime <= elapsedTime)
			{
				destroyParticleEffect(i);
			}
			else
			{
				std::vector<unsigned int>& emitters = m_effects[i].emitters;
				unsigned int j = 0;
				while(j < emitters.size())
				{
					const ParticleEmitter& emitter = m_particleSystem.getParticleEmitter(emitters[j]);
					if (emitter.spawnTime <= elapsedTime)
					{
						m_particleSystem.createParticleEmitter(emitter);
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