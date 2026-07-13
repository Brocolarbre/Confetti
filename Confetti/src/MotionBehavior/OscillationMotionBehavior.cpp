#include "Confetti/MotionBehavior/OscillationMotionBehavior.hpp"

namespace cft
{
	OscillationMotionBehavior::OscillationMotionBehavior(const glm::vec3& from, const glm::vec3& to, float speed) :
		m_from(from),
		m_to(to),
		m_speed(speed)
	{

	}

	glm::vec3 OscillationMotionBehavior::evaluate(float age, const MotionState& motionState)
	{
		float t = age * m_speed;

		return glm::mix(m_from, m_to, (1.0f - std::cos(t)) * 0.5f);
	}
}