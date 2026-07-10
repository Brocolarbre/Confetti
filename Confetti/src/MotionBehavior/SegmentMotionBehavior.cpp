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

	void SegmentMotionBehavior::update(float elapsedTime, float deltaTime, Transform& transform)
	{
		float t = elapsedTime * m_speed;

		transform.position = glm::mix(m_from, m_to, t);
	}
}