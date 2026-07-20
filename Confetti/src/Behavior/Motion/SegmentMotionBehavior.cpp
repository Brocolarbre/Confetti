#include "Confetti/Behavior/Motion/SegmentMotionBehavior.hpp"

namespace cft
{
	SegmentMotionBehavior::SegmentMotionBehavior(const glm::vec3& from, const glm::vec3& to, float speed) :
		m_from(from),
		m_to(to),
		m_speed(speed)
	{

	}

	glm::vec3 SegmentMotionBehavior::evaluate(float age, const MotionState& motionState)
	{
		float t = age * m_speed;

		return glm::mix(m_from, m_to, t);
	}
}