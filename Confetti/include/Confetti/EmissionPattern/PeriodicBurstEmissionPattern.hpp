#pragma once

#include "EmissionPattern.hpp"

namespace cft
{
	class PeriodicBurstEmissionPattern : public EmissionPattern
	{
	private:
		unsigned int m_count;
		float m_interval;
		float m_accumulator;

	public:
		PeriodicBurstEmissionPattern(unsigned int count, float interval);

		unsigned int getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const;
		unsigned int emit(float deltaTime) override;
		std::unique_ptr<EmissionPattern> clone() const override;
	};
}