#include "Confetti/ForceField/LinearDragForceField.hpp"

namespace cft
{
	LinearDragForceField::LinearDragForceField(float strength) :
		m_strength(glm::clamp(strength, 0.0f, 1.0f))
	{

	}

	std::unique_ptr<ForceField> LinearDragForceField::clone() const
	{
		return std::make_unique<LinearDragForceField>(*this);
	}

	MotionAcceleration LinearDragForceField::evaluate(const MotionState& motionState) const
	{
		return MotionAcceleration{ -m_strength * motionState.linearVelocity, glm::vec3(0.0f) };
	}
}