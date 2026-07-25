#pragma once

#include "VisualBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class CONFETTI_API FadeInVisualBehavior : public Cloneable<FadeInVisualBehavior, VisualBehavior>
	{
	private:
		ParticleTime m_duration;

	public:
		FadeInVisualBehavior(ParticleTime duration);

		void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) override;
	};
}