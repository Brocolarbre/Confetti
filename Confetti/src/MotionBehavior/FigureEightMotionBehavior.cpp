#include "Confetti/MotionBehavior/FigureEightMotionBehavior.hpp"

namespace cft
{
	FigureEightMotionBehavior::FigureEightMotionBehavior(const glm::vec3& axis, float radius, float speed) :
		m_axis(glm::normalize(axis)),
		m_radius(radius),
		m_speed(speed),
		m_tangent(),
		m_bitangent()
	{
		glm::vec3 up = (std::abs(m_axis.y) < 0.999f) ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(1.0f, 0.0f, 0.0f);
		m_tangent = glm::normalize(glm::cross(up, m_axis));
		m_bitangent = glm::cross(m_axis, m_tangent);
	}

	glm::vec3 FigureEightMotionBehavior::evaluate(float elapsedTime, const MotionState& motionState)
	{
		float t = elapsedTime * m_speed;

		glm::vec3 localPosition(m_radius * std::sin(t), 0.0f, m_radius * std::sin(t) * std::cos(t) * 0.5f);
		return m_tangent * localPosition.x + m_axis * localPosition.y + m_bitangent * localPosition.z;
	}
}