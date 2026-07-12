#pragma once

#include "EmissionPattern.hpp"

namespace cft
{
	class LinearRateEmissionPattern : public Cloneable<LinearRateEmissionPattern, EmissionPattern>
	{
	private:
		float m_initialRate;
		float m_finalRate;
		float m_transitionDuration;
		float m_accumulator;
		float m_elapsedTime;

	public:
		LinearRateEmissionPattern(float initialRate, float finalRate, float transitionDuration);

		unsigned int getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const override;
		unsigned int emit(float deltaTime) override;
	};
}