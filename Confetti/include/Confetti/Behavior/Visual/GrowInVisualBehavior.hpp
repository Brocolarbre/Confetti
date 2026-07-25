#pragma once

#include "VisualBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class CONFETTI_API GrowInVisualBehavior : public Cloneable<GrowInVisualBehavior, VisualBehavior>
	{
	private:
		ParticleTime m_duration;

	public:
		GrowInVisualBehavior(ParticleTime duration);

		void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) override;
	};
}