#include "Confetti/MotionBehavior/OrbitMotionBehavior.hpp"

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

	std::unique_ptr<MotionBehavior> OrbitMotionBehavior::clone() const
	{
		return std::make_unique<OrbitMotionBehavior>(*this);
	}

	glm::vec3 OrbitMotionBehavior::evaluate(float elapsedTime, const MotionState& motionState)
	{
		float t = elapsedTime * m_speed;

		glm::vec3 offset = std::cos(t) * m_tangent * m_radius + std::sin(t) * m_bitangent * m_radius;
		return m_origin + offset;
	}
}