#include "Confetti/Behavior/Force/WindForceField.hpp"

namespace cft
{
	WindForceField::WindForceField(const glm::vec3& direction, float strength, float drag) :
		m_velocity(glm::normalize(direction) * strength),
		m_drag(drag)
	{

	}

	MotionAcceleration WindForceField::evaluate(const MotionState& motionState) const
	{
		glm::vec3 relativeVelocity = motionState.linearVelocity - m_velocity;
		return MotionAcceleration{ -m_drag * relativeVelocity * glm::length(relativeVelocity), glm::vec3(0.0f) };
	}
}