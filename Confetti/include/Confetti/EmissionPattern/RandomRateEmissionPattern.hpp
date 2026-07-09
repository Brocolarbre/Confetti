#pragma once

#include "EmissionPattern.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class RandomRateEmissionPattern : public EmissionPattern
	{
	private:
		float m_minimumRate;
		float m_maximumRate;
		float m_accumulator;
		RandomNumberGenerator& m_randomNumberGenerator;

	public:
		RandomRateEmissionPattern(float minimumRate, float maximumRate, RandomNumberGenerator& randomNumberGenerator);

		unsigned int getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const;
		unsigned int emit(float deltaTime) override;
		std::unique_ptr<EmissionPattern> clone() const override;
	};
}