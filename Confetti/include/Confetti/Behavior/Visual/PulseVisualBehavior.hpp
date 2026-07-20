#pragma once

#include "VisualBehavior.hpp"

namespace cft
{
	class PulseVisualBehavior : public Cloneable<PulseVisualBehavior, VisualBehavior>
	{
	private:
		glm::vec4 m_colorA;
		glm::vec4 m_colorB;
		float m_speed;

	public:
		PulseVisualBehavior(const glm::vec4& colorA, const glm::vec4& colorB, float speed);

		void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) override;
	};
}