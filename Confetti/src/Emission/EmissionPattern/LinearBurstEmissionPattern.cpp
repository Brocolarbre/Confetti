#include "Confetti/Emission/EmissionPattern/LinearBurstEmissionPattern.hpp"

#include <cmath>

namespace cft
{
	LinearBurstEmissionPattern::LinearBurstEmissionPattern(unsigned int count, float initialInterval, float finalInterval, float transitionDuration) :
		m_count(count),
		m_initialInterval(initialInterval),
		m_finalInterval(finalInterval),
		m_transitionDuration(std::max(transitionDuration, 0.0f)),
		m_accumulator(m_initialInterval),
		m_elapsedTime(0.0f)
	{

	}

	unsigned int LinearBurstEmissionPattern::getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const
	{
		return static_cast<unsigned int>(std::ceil(maximumParticleLifetime / std::min(m_initialInterval, m_finalInterval)) * m_count);
	}

	unsigned int LinearBurstEmissionPattern::emit(float deltaTime)
	{
		m_elapsedTime += deltaTime;

		float alpha = m_transitionDuration == 0.0f ? 1.0f : std::min(m_elapsedTime / m_transitionDuration, 1.0f);
		float interval = m_initialInterval + (m_finalInterval - m_initialInterval) * alpha;

		m_accumulator += deltaTime;

		if (m_accumulator < interval)
			return 0;

		unsigned int bursts = 0;

		while (m_accumulator >= interval)
		{
			++bursts;
			m_accumulator -= interval;
		}

		return m_count;
	}
}