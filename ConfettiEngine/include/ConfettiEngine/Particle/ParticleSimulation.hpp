#pragma once

#include "ParticleSystem.hpp"

#include <Krono/Krono.hpp>

namespace cft
{
	class ParticleSimulation
	{
	private:
		krono::Chronometer m_chronometer;
		krono::Chronometer m_frameChronometer;
		ParticleSystem m_particleSystem; // Instantiate outside ? (ConfettiInstance)
		unsigned int m_spawnRate;
		float m_maxLifetime;
		float m_spawnAccumulator;

		unsigned int getMaximumParticleCount() const;

	public:
		ParticleSimulation();

		const ParticleSystem& getParticleSystem() const;

		void update();
	};
}