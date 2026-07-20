#pragma once

#include "VisualBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class ShrinkOutVisualBehavior : public Cloneable<ShrinkOutVisualBehavior, VisualBehavior>
	{
	private:
		ParticleTime m_duration;

	public:
		ShrinkOutVisualBehavior(ParticleTime duration);

		void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) override;
	};
}