#include "Confetti/EmissionPattern/FixedBurstEmissionPattern.hpp"

#include <cmath>

namespace cft
{
	FixedBurstEmissionPattern::FixedBurstEmissionPattern(unsigned int count, unsigned int burstCount, float interval) :
		m_count(count),
		m_burstCount(burstCount),
		m_interval(interval),
		m_accumulator(interval),
		m_burstAccumulator(0)
	{

	}

	unsigned int FixedBurstEmissionPattern::getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const
	{
		return std::min(m_burstCount, static_cast<unsigned int>(std::ceil(maximumParticleLifetime / m_interval))) * m_count;
	}

	unsigned int FixedBurstEmissionPattern::emit(float deltaTime)
	{
		if (m_burstAccumulator == m_burstCount)
			return 0;

		m_accumulator += deltaTime;

		if (m_accumulator < m_interval)
			return 0;

		++m_burstAccumulator;
		m_accumulator -= m_interval;

		return m_count;



		m_accumulator += deltaTime;

		unsigned int bursts = 0;

		while (m_accumulator >= m_interval && m_burstAccumulator < m_burstCount)
		{
			m_accumulator -= m_interval;
			++m_burstAccumulator;
			++bursts;
		}

		return bursts * m_count;
	}

	std::unique_ptr<EmissionPattern> FixedBurstEmissionPattern::clone() const
	{
		return std::make_unique<FixedBurstEmissionPattern>(*this);
	}
}