#include "Confetti/Behavior/Force/QuadraticDragForceField.hpp"

namespace cft
{
	QuadraticDragForceField::QuadraticDragForceField(float strength) :
		m_strength(glm::clamp(strength, 0.0f, 1.0f))
	{

	}

	MotionAcceleration QuadraticDragForceField::evaluate(const MotionState& motionState) const
	{
		return MotionAcceleration{ -m_strength * motionState.linearVelocity * glm::length(motionState.linearVelocity), glm::vec3(0.0f) };
	}
}