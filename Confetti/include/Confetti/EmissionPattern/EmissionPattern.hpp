#pragma once

#include "Confetti/Tools/Cloneable.hpp"

namespace cft
{
	class EmissionPattern
	{
	public:
		virtual ~EmissionPattern() = default;

		virtual std::unique_ptr<EmissionPattern> clone() const = 0;
		virtual unsigned int getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const = 0;
		virtual unsigned int emit(float deltaTime) = 0;
	};
}