#pragma once

#include "Confetti/Particle/Particle.hpp"

#include <memory>

namespace cft
{
	class ParticleSpawner
	{
	public:
		virtual ~ParticleSpawner() = default;

		virtual std::unique_ptr<ParticleSpawner> clone() const = 0;
		virtual float getMaxiumParticleLifetime() const = 0;
		virtual std::vector<Particle> spawn(unsigned int count, float elapsedTime, float deltaTime, unsigned int id) = 0;
	};
}