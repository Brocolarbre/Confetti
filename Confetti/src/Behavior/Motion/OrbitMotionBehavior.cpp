#include "Confetti/Behavior/Motion/OrbitMotionBehavior.hpp"

namespace cft
{
	OrbitMotionBehavior::OrbitMotionBehavior(const glm::vec3& origin, const glm::vec3& axis, float radius, float speed) :
		m_origin(origin),
		m_axis(axis),
		m_radius(radius),
		m_speed(speed),
		m_tangent(),
		m_bitangent()
	{
		glm::vec3 up = (std::abs(m_axis.y) < 0.999f) ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(1.0f, 0.0f, 0.0f);
		m_tangent = glm::normalize(glm::cross(up, m_axis));
		m_bitangent = glm::cross(m_axis, m_tangent);
	}

	glm::vec3 OrbitMotionBehavior::evaluate(float age, const MotionState& motionState)
	{
		float t = age * m_speed;

		glm::vec3 offset = std::cos(t) * m_tangent * m_radius + std::sin(t) * m_bitangent * m_radius;
		return m_origin + offset;
	}
}