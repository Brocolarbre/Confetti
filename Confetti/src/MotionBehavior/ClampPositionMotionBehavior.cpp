#include "Confetti/MotionBehavior/ClampPositionMotionBehavior.hpp"

namespace cft
{
	ClampPositionMotionBehavior::ClampPositionMotionBehavior(const glm::vec3& minimumPosition, const glm::vec3& maximumPosition) :
		m_minimumPosition(minimumPosition),
		m_maximumPosition(maximumPosition)
	{

	}

	std::unique_ptr<MotionBehavior> ClampPositionMotionBehavior::clone() const
	{
		return std::make_unique<ClampPositionMotionBehavior>(*this);
	}

	void ClampPositionMotionBehavior::update(float elapsedTime, float deltaTime, Transform& transform)
	{
		transform.position = glm::clamp(transform.position, m_minimumPosition, m_maximumPosition);
	}
}