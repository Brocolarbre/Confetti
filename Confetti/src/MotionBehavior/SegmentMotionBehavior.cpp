#include "Confetti/MotionBehavior/SegmentMotionBehavior.hpp"

namespace cft
{
	SegmentMotionBehavior::SegmentMotionBehavior(const glm::vec3& from, const glm::vec3& to, float speed) :
		m_from(from),
		m_to(to),
		m_speed(speed)
	{

	}

	std::unique_ptr<MotionBehavior> SegmentMotionBehavior::clone() const
	{
		return std::make_unique<SegmentMotionBehavior>(*this);
	}

	glm::vec3 SegmentMotionBehavior::evaluate(float elapsedTime, const MotionState& motionState)
	{
		float t = elapsedTime * m_speed;

		return glm::mix(m_from, m_to, t);
	}
}