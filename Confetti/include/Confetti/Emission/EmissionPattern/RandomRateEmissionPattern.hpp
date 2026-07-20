#pragma once

#include "EmissionPattern.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	class RandomRateEmissionPattern : public Cloneable<RandomRateEmissionPattern, EmissionPattern>
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
	};
}