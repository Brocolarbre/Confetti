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
		virtual void evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle) = 0;
	};
}