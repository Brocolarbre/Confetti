#pragma once

#include "Confetti/Export.hpp"
#include "Confetti/Tool/Cloneable.hpp"

namespace cft
{
	class CONFETTI_API EmissionPattern
	{
	public:
		virtual ~EmissionPattern() = default;

		virtual std::unique_ptr<EmissionPattern> clone() const = 0;
		virtual unsigned int getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const = 0;
		virtual unsigned int emit(float deltaTime) = 0;
	};
}