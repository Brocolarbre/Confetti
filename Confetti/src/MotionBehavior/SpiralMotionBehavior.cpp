#include "Confetti/MotionBehavior/SpiralMotionBehavior.hpp"

namespace cft
{
	SpiralMotionBehavior::SpiralMotionBehavior(const glm::vec3& origin, const glm::vec3& axis, float startRadius, float growth, float speed, float rise) :
		m_origin(origin),
		m_axis(glm::normalize(axis)),
		m_startRadius(startRadius),
		m_growth(growth),
		m_speed(speed),
		m_rise(rise),
		m_tangent(),
		m_bitangent()
	{
		glm::vec3 up = (std::abs(m_axis.y) < 0.999f) ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(1.0f, 0.0f, 0.0f);
		m_tangent = glm::normalize(glm::cross(up, m_axis));
		m_bitangent = glm::cross(m_axis, m_tangent);
	}

	std::unique_ptr<MotionBehavior> SpiralMotionBehavior::clone() const
	{
		return std::make_unique<SpiralMotionBehavior>(*this);
	}

	void SpiralMotionBehavior::update(float elapsedTime, float deltaTime, Transform& transform)
	{
		float t = elapsedTime * m_speed;
		float radius = m_startRadius + m_growth * elapsedTime;

		glm::vec3 offset = m_tangent * (std::cos(t) * radius) + m_bitangent * (std::sin(t) * radius) + m_axis * (m_rise * t);
		transform.position = m_origin + offset;
	}
}