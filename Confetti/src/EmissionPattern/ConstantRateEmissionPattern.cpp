#include "Confetti/EmissionPattern/ConstantRateEmissionPattern.hpp"

#include <cmath>

namespace cft
{
	ConstantRateEmissionPattern::ConstantRateEmissionPattern(float rate) :
		m_rate(rate),
		m_accumulator(0.0f)
	{

	}

	unsigned int ConstantRateEmissionPattern::getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const
	{
		return static_cast<unsigned int>(std::ceil(m_rate * maximumParticleLifetime));
	}

	unsigned int ConstantRateEmissionPattern::emit(float deltaTime)
	{
		m_accumulator += m_rate * deltaTime;

		unsigned int emissionCount = static_cast<unsigned int>(m_accumulator);
		m_accumulator -= emissionCount;

		return emissionCount;
	}

	std::unique_ptr<EmissionPattern> ConstantRateEmissionPattern::clone() const
	{
		return std::make_unique<ConstantRateEmissionPattern>(*this);
	}
}