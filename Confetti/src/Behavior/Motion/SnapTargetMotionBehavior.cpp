#include "Confetti/Behavior/Motion/SnapTargetMotionBehavior.hpp"

namespace cft
{
	SnapTargetMotionBehavior::SnapTargetMotionBehavior(std::function<glm::vec3()> targetProvider) :
		m_targetProvider(std::move(targetProvider))
	{

	}

	glm::vec3 SnapTargetMotionBehavior::evaluate(float age, const MotionState& motionState)
	{
		return m_targetProvider() - motionState.position;
	}
}