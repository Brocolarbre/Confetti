#pragma once

#include "Confetti/Simulation/Pool/ParticlePool.hpp"
#include "Confetti/Tool/Cloneable.hpp"
#include "Confetti/Tool/Seedable.hpp"

namespace cft
{
	class CONFETTI_API VisualBehavior : public Seedable
	{
	public:
		virtual ~VisualBehavior() = default;

		virtual std::unique_ptr<VisualBehavior> clone() const = 0;

		virtual void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) = 0;
	};
}