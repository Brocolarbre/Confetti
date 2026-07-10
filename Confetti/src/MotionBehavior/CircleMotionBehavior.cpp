#include "Confetti/MotionBehavior/CircleMotionBehavior.hpp"

namespace cft
{
	CircleMotionBehavior::CircleMotionBehavior(const glm::vec3& axis, float radius, float speed) :
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

	std::unique_ptr<MotionBehavior> CircleMotionBehavior::clone() const
	{
		return std::make_unique<CircleMotionBehavior>(*this);
	}

	void CircleMotionBehavior::update(float elapsedTime, float deltaTime, Transform& transform)
	{
		float t = elapsedTime * m_speed;

		glm::vec3 localPosition(std::cos(t) * m_radius, 0.0f, glm::sin(t) * m_radius);
		transform.position = m_tangent * localPosition.x + m_axis * localPosition.y + m_bitangent * localPosition.z;
	}
}