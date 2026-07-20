#pragma once

#include "Confetti/Simulation/Core/Particle.hpp"
#include "Confetti/Tool/Cloneable.hpp"

namespace cft
{
	class VisualBehavior
	{
	public:
		virtual ~VisualBehavior() = default;

		virtual std::unique_ptr<VisualBehavior> clone() const = 0;
		virtual void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) = 0;
	};
}