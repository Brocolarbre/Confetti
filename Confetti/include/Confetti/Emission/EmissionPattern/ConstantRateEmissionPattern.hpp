#pragma once

#include "EmissionPattern.hpp"

namespace cft
{
	class ConstantRateEmissionPattern : public Cloneable<ConstantRateEmissionPattern, EmissionPattern>
	{
	private:
		float m_rate;
		float m_accumulator;

	public:
		ConstantRateEmissionPattern(float rate);

		unsigned int getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const override;
		unsigned int emit(float deltaTime) override;
	};
}