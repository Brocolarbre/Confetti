#pragma once

#include "EmissionPattern.hpp"

namespace cft
{
	class LinearBurstEmissionPattern : public Cloneable<LinearBurstEmissionPattern, EmissionPattern>
	{
	private:
		unsigned int m_count;
		float m_initialInterval;
		float m_finalInterval;
		float m_transitionDuration;		
		float m_accumulator;
		float m_elapsedTime;

	public:
		LinearBurstEmissionPattern(unsigned int count, float initialInterval, float finalInterval, float transitionDuration);

		unsigned int getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const override;
		unsigned int emit(float deltaTime) override;
	};
}