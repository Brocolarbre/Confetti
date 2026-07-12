#include "Confetti/EmissionPattern/LinearRateEmissionPattern.hpp"

#include <cmath>

namespace cft
{
	LinearRateEmissionPattern::LinearRateEmissionPattern(float initialRate, float finalRate, float transitionDuration) :
		m_initialRate(initialRate),
		m_finalRate(finalRate),
		m_transitionDuration(std::max(transitionDuration, 0.0f)),
		m_accumulator(0.0f),
		m_elapsedTime(0.0f)
	{

	}

	unsigned int LinearRateEmissionPattern::getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const
	{
		return static_cast<unsigned int>(std::ceil(std::max(m_initialRate, m_finalRate) * maximumParticleLifetime));
	}

	unsigned int LinearRateEmissionPattern::emit(float deltaTime)
	{
		m_elapsedTime += deltaTime;

		float alpha = m_transitionDuration == 0.0f ? 1.0f : std::min(m_elapsedTime / m_transitionDuration, 1.0f);
		float rate = m_initialRate + (m_finalRate - m_initialRate) * alpha;

		m_accumulator += rate * deltaTime;

		unsigned int emissionCount = static_cast<unsigned int>(m_accumulator);
		m_accumulator -= emissionCount;

		return emissionCount;
	}
}