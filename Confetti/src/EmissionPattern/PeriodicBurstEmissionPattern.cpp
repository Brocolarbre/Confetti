#include "Confetti/EmissionPattern/PeriodicBurstEmissionPattern.hpp"

#include <cmath>

namespace cft
{
	PeriodicBurstEmissionPattern::PeriodicBurstEmissionPattern(unsigned int count, float interval) :
		m_count(count),
		m_interval(interval),
		m_accumulator(interval)
	{

	}

	unsigned int PeriodicBurstEmissionPattern::getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const
	{
		return static_cast<unsigned int>(std::ceil(maximumParticleLifetime / m_interval) * m_count);
	}

	unsigned int PeriodicBurstEmissionPattern::emit(float deltaTime)
	{
		m_accumulator += deltaTime;

		if (m_accumulator < m_interval)
			return 0;

		m_accumulator -= m_interval;

		return m_count;
	}

	std::unique_ptr<EmissionPattern> PeriodicBurstEmissionPattern::clone() const
	{
		return std::make_unique<PeriodicBurstEmissionPattern>(*this);
	}
}