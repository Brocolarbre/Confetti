#include "Confetti/ForceField/LinearDragForceField.hpp"

namespace cft
{
	LinearDragForceField::LinearDragForceField(float strength) :
		m_strength(glm::clamp(strength, 0.0f, 1.0f))
	{

	}

	MotionAcceleration LinearDragForceField::evaluate(const MotionState& motionState) const
	{
		return MotionAcceleration{ -m_strength * motionState.linearVelocity, glm::vec3(0.0f) };
	}
}