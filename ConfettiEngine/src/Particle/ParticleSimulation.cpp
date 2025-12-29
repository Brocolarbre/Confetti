#include "ConfettiEngine/Particle/ParticleSimulation.hpp"

#include <iostream>

namespace cft
{
	unsigned int ParticleSimulation::getMaximumParticleCount() const
	{
		return static_cast<unsigned int>(m_maxLifetime * m_spawnRate);
	}

	ParticleSimulation::ParticleSimulation() :
		m_chronometer(),
		m_frameChronometer(),
		m_particleSystem(),
		m_spawnRate(10),
		m_maxLifetime(5.0f),
		m_spawnAccumulator(0.0f)
	{
		// Initialize, boundaries
		unsigned int maximumParticleCount = getMaximumParticleCount();
		m_particleSystem.allocate(maximumParticleCount);

		m_chronometer.restart();
		m_frameChronometer.restart();
	}

	const ParticleSystem& ParticleSimulation::getParticleSystem() const
	{
		return m_particleSystem;
	}

	void ParticleSimulation::update()
	{
		ParticleData& particleData = m_particleSystem.getParticleData();
		unsigned int particleCount = m_particleSystem.getParticleCount();
		float elapsedTime = static_cast<float>(m_chronometer.getElapsedTime().seconds);

		for (unsigned int i = 0; i < particleCount; ) {
			float timeOfDeath = particleData.spawnTime[i] + particleData.lifetime[i];

			float progress = elapsedTime / timeOfDeath;
			if (timeOfDeath <= elapsedTime)
			{
				m_particleSystem.killParticle(i);
				particleCount = m_particleSystem.getParticleCount();
			}
			else
			{
				++i;
			}
		}

		// Spawn particles
		float deltaTime = static_cast<float>(m_frameChronometer.getElapsedTime().seconds);
		m_frameChronometer.restart();

		float spawnCount = m_spawnRate * deltaTime + m_spawnAccumulator;
		m_spawnAccumulator = spawnCount - glm::floor(spawnCount);

		unsigned int roundedSpawnCount = static_cast<unsigned int>(spawnCount);

		for (unsigned int i = 0; i < roundedSpawnCount; ++i)
			m_particleSystem.spawnParticle(elapsedTime);

		// Physics

		for (unsigned int i = 0; i < particleCount; ++i)
			particleData.position[i] += particleData.velocity[i] * deltaTime;
	}
}