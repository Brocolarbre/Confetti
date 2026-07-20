#pragma once

#include "VisualBehavior.hpp"

namespace cft
{
	class FlickerVisualBehavior : public Cloneable<FlickerVisualBehavior, VisualBehavior>
	{
	private:
		float m_minimumBrightness;
		float m_maximumBrightness;
		float m_speed;

	public:
		FlickerVisualBehavior(float minimumBrightness, float maximumBrightness, float speed);

		void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) override;
	};
}