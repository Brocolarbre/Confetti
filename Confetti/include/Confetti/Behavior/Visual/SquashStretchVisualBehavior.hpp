#pragma once

#include "VisualBehavior.hpp"

namespace cft
{
	class CONFETTI_API SquashStretchVisualBehavior : public Cloneable<SquashStretchVisualBehavior, VisualBehavior>
	{
	private:
		glm::vec2 m_strength;
		float m_speed;

	public:
		SquashStretchVisualBehavior(const glm::vec2& strength, float speed);

		void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) override;
	};
}