#pragma once

#include "VisualBehavior.hpp"

namespace cft
{
	class SmoothColorShiftVisualBehavior : public Cloneable<SmoothColorShiftVisualBehavior, VisualBehavior>
	{
	private:
		std::vector<glm::vec4> m_colors;
		float m_speed;
		bool m_cyclic;

	public:
		SmoothColorShiftVisualBehavior(const std::vector<glm::vec4>& colors, float speed, bool cyclic);

		void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) override;
	};
}