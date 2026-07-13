#pragma once

#include "Confetti/Particle/Particle.hpp"
#include "Confetti/Tools/Cloneable.hpp"

namespace cft
{
	class ParticleBehavior
	{
	public:
		virtual ~ParticleBehavior() = default;

		virtual std::unique_ptr<ParticleBehavior> clone() const = 0;
		virtual void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) = 0;
	};
}