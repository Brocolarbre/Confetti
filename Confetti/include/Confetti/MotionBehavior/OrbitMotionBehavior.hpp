#pragma once

#include "MotionBehavior.hpp"

namespace cft
{
	class OrbitMotionBehavior : public CloneableMotionBehavior<OrbitMotionBehavior>
	{
	private:
		glm::vec3 m_origin;
		glm::vec3 m_axis;
		float m_radius;
		float m_speed;

		glm::vec3 m_tangent;
		glm::vec3 m_bitangent;

	public:
		OrbitMotionBehavior(const glm::vec3& origin, const glm::vec3& axis, float radius, float speed);

		glm::vec3 evaluate(float elapsedTime, const MotionState& motionState) override;
	};
}