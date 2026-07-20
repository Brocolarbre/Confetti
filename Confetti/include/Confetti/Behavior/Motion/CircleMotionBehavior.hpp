#pragma once

#include "MotionBehavior.hpp"

namespace cft
{
	class CircleMotionBehavior : public Cloneable<CircleMotionBehavior, MotionBehavior>
	{
	private:
		glm::vec3 m_axis;
		float m_radius;
		float m_speed;

		glm::vec3 m_tangent;
		glm::vec3 m_bitangent;

	public:
		CircleMotionBehavior(const glm::vec3& axis, float radius, float speed);

		glm::vec3 evaluate(float age, const MotionState& motionState) override;
	};
}