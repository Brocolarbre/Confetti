#pragma once

#include "Confetti/Particle/Particle.hpp"

#include <memory>

namespace cft
{
	class ParticleBehavior
	{
	public:
		virtual ~ParticleBehavior() = default;

		virtual std::unique_ptr<ParticleBehavior> clone() const = 0;
		virtual void update(float elapsedTime, float deltaTime, ParticleView& particle) = 0;
	};
}