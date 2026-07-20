#include "Confetti/Behavior/Force/DirectionalForceField.hpp"

namespace cft
{
	DirectionalForceField::DirectionalForceField(const glm::vec3& direction, float strength) :
		m_direction(glm::normalize(direction)),
		m_strength(strength)
	{

	}

	MotionAcceleration DirectionalForceField::evaluate(const MotionState& motionState) const
	{
		return MotionAcceleration{ m_direction * m_strength, glm::vec3(0.0f) };
	}
}