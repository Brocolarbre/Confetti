#include "ConfettiEngine/Particle/ParticleEmitterPool.hpp"
#include "ConfettiEngine/Particle/ParticleGenerator.hpp"

namespace cft
{
	ParticleEmitterPool::ParticleEmitterPool(RandomNumberGenerator& generator) :
		m_emitters(),
		m_particles(),
		m_generator(generator)
	{
		ParticleBoundaries boundaries{ glm::vec4(0.0f), glm::vec4(1.0f), glm::vec3(-10.0f), glm::vec3(10.0f), glm::vec3(-1.0f), glm::vec3(1.0f), glm::vec2(0.01f), glm::vec2(1.0f), 2.0f, 5.0f };
		ParticleEmitter emitter{ 20, 0.0f, boundaries };
		m_emitters.push_back(emitter);
		m_particles.allocate(static_cast<unsigned int>(emitter.spawnRate * boundaries.maximumLifetime));
	}

	const ParticlePool& ParticleEmitterPool::getParticlePool() const
	{
		return m_particles;
	}

	void ParticleEmitterPool::update(float elapsedTime, float deltaTime)
	{
		// Despawn
		unsigned int i = 0;
		while (i < m_particles.count)
		{
			float despawnTime = m_particles.spawnTime[i] + m_particles.lifetime[i];
			float progress = elapsedTime / despawnTime;

			if (despawnTime <= elapsedTime)
				m_particles.remove(i);
			else
				++i;
		}

		// Spawn
		for (ParticleEmitter& emitter : m_emitters)
		{
			float spawnCount = emitter.spawnRate * deltaTime + emitter.accumulator;
			emitter.accumulator = spawnCount - glm::floor(spawnCount);

			unsigned int roundedSpawnCount = static_cast<unsigned int>(spawnCount);
			for (unsigned int i = 0; i < roundedSpawnCount; ++i)
				m_particles.add(ParticleGenerator::generateParticle(m_generator, emitter.boundaries, elapsedTime));
		}

		// Physics
		for (unsigned int i = 0; i < m_particles.count; ++i)
			m_particles.position[i] += m_particles.velocity[i] * deltaTime;
	}
}