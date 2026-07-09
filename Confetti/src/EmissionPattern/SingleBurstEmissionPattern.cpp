#include "Confetti/EmissionPattern/SingleBurstEmissionPattern.hpp"

namespace cft
{
	SingleBurstEmissionPattern::SingleBurstEmissionPattern(unsigned int count) :
		m_count(count),
		m_hasEmitted(false)
	{

	}

	unsigned int SingleBurstEmissionPattern::getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const
	{
		return m_count;
	}

	unsigned int SingleBurstEmissionPattern::emit(float deltaTime)
	{
		if (m_hasEmitted)
			return 0;

		m_hasEmitted = true;
		return m_count;
	}

	std::unique_ptr<EmissionPattern> SingleBurstEmissionPattern::clone() const
	{
		return std::make_unique<SingleBurstEmissionPattern>(*this);
	}
}