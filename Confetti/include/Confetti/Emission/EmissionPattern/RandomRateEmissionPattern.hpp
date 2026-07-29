#pragma once

#include "EmissionPattern.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	class CONFETTI_API RandomRateEmissionPattern : public Cloneable<RandomRateEmissionPattern, EmissionPattern>
	{
	private:
		float m_minimumRate;
		float m_maximumRate;
		float m_accumulator;
		RandomNumberGenerator m_randomNumberGenerator;

	public:
		RandomRateEmissionPattern(float minimumRate, float maximumRate, std::uint64_t seed = 0);

		std::optional<std::uint64_t> getSeed() const override;
		void setSeed(std::uint64_t seed) override;

		unsigned int getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const;
		unsigned int emit(float deltaTime) override;
	};
}