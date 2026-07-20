#pragma once

#include "VisualBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class FadeOutVisualBehavior : public Cloneable<FadeOutVisualBehavior, VisualBehavior>
	{
	private:
		ParticleTime m_duration;

	public:
		FadeOutVisualBehavior(ParticleTime duration);

		void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) override;
	};
}