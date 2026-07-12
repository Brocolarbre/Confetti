#pragma once

#include "MotionBehavior.hpp"

namespace cft
{
	class FigureEightMotionBehavior : public Cloneable<FigureEightMotionBehavior, MotionBehavior>
	{
	private:
		glm::vec3 m_axis;
		float m_radius;
		float m_speed;

		glm::vec3 m_tangent;
		glm::vec3 m_bitangent;

	public:
		FigureEightMotionBehavior(const glm::vec3& axis, float radius, float speed);

		glm::vec3 evaluate(float elapsedTime, const MotionState& motionState) override;
	};
}