#pragma once

#include "EmissionPattern.hpp"

namespace cft
{
	class FixedBurstEmissionPattern : public Cloneable<FixedBurstEmissionPattern, EmissionPattern>
	{
	private:
		unsigned int m_count;
		unsigned int m_burstCount;
		float m_interval;
		float m_accumulator;
		unsigned int m_burstAccumulator;

	public:
		FixedBurstEmissionPattern(unsigned int count, unsigned int burstCount, float interval);

		unsigned int getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const;
		unsigned int emit(float deltaTime) override;
	};
}