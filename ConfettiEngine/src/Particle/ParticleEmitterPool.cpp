#include "ConfettiEngine/Particle/ParticleEmitterPool.hpp"
#include "ConfettiEngine/Particle/ParticleGenerator.hpp"

namespace cft
{
	ParticleEmitterPool::ParticleEmitterPool(RandomNumberGenerator& generator) :
		m_emitters(),
		m_capacity(0),
		m_count(0),
		m_particlePool(),
		m_generator(generator)
	{
		
	}

	unsigned int ParticleEmitterPool::getCapacity() const
	{
		return m_capacity;
	}

	unsigned int ParticleEmitterPool::getCount() const
	{
		return m_count;
	}

	const ParticlePool& ParticleEmitterPool::getParticlePool() const
	{
		return m_particlePool;
	}

	void ParticleEmitterPool::createParticleEmitter(const ParticleEmitter& emitter)
	{
		unsigned int newIndex = m_count++;
		m_emitters[newIndex] = emitter;
		
		unsigned int emitterMaximumParticleCount = static_cast<unsigned int>(emitter.spawnRate * emitter.boundaries.maximumLifetime);
		unsigned int particlePoolCapacity = m_particlePool.getCapacity();
		if(particlePoolCapacity - m_particlePool.getCount() < emitterMaximumParticleCount)
			m_particlePool.resize(particlePoolCapacity + emitterMaximumParticleCount);
	}

	void ParticleEmitterPool::destroyParticleEmitter(unsigned int index)
	{
		unsigned int lastIndex = --m_count;
		m_emitters[index] = m_emitters[lastIndex];
	}

	void ParticleEmitterPool::resize(unsigned int capacity)
	{
		m_emitters.resize(capacity);
	}

	void ParticleEmitterPool::update(float elapsedTime, float deltaTime)
	{
		m_particlePool.update(elapsedTime, deltaTime);

		unsigned int i = 0;
		while (i < m_count)
		{
			float despawnTime = m_emitters[i].spawnTime + m_emitters[i].lifetime;
			if (despawnTime <= elapsedTime)
			{
				destroyParticleEmitter(i);
			}
			else
			{
				float spawnCount = m_emitters[i].spawnRate * deltaTime + m_emitters[i].accumulator;
				m_emitters[i].accumulator = spawnCount - glm::floor(spawnCount);

				unsigned int roundedSpawnCount = static_cast<unsigned int>(spawnCount);
				for (unsigned int j = 0; j < roundedSpawnCount; ++j)
					m_particlePool.createParticle(ParticleGenerator::generateParticle(m_generator, m_emitters[i].boundaries, elapsedTime));

				++i;
			}
		}
	}
}