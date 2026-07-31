#include "Confetti/Behavior/Force/FollowTargetForceField.hpp"

namespace cft
{
	FollowTargetForceField::FollowTargetForceField(std::function<glm::vec3()> targetProvider, float responseTime, float dampingRatio) :
		m_targetProvider(std::move(targetProvider)),
		m_spring(),
		m_damping()
	{
		float omega = 2.0f / glm::max(responseTime, 0.05f);

		m_spring = omega * omega;
		m_damping = 2.0f * dampingRatio * omega;
	}

	MotionAcceleration FollowTargetForceField::evaluate(const MotionState& motionState)
	{
		glm::vec3 offset = m_targetProvider() - motionState.position;
		glm::vec3 acceleration = m_spring * offset - m_damping * motionState.linearVelocity;

		return MotionAcceleration{ acceleration, glm::vec3(0.0f) };
	}
}