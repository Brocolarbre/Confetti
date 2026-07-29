#include "Confetti/Emission/EmissionPattern/RandomRateEmissionPattern.hpp"

#include <cmath>

namespace cft
{
	RandomRateEmissionPattern::RandomRateEmissionPattern(float minimumRate, float maximumRate, std::uint64_t seed) :
		m_minimumRate(minimumRate),
		m_maximumRate(maximumRate),
		m_accumulator(0.0f),
		m_randomNumberGenerator(seed)
	{

	}

	std::optional<std::uint64_t> RandomRateEmissionPattern::getSeed() const
	{
		return m_randomNumberGenerator.getSeed();
	}

	void RandomRateEmissionPattern::setSeed(std::uint64_t seed)
	{
		m_randomNumberGenerator.setSeed(seed);
	}

	unsigned int RandomRateEmissionPattern::getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const
	{
		return static_cast<unsigned int>(std::ceil(m_maximumRate * maximumParticleLifetime));
	}

	unsigned int RandomRateEmissionPattern::emit(float deltaTime)
	{
		float rate = m_randomNumberGenerator.generate(m_minimumRate, m_maximumRate);
		m_accumulator += rate * deltaTime;

		unsigned int emissionCount = static_cast<unsigned int>(m_accumulator);
		m_accumulator -= emissionCount;

		return emissionCount;
	}
}