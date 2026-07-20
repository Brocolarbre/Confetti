#include "Confetti/Behavior/Force/TurbulenceForceField.hpp"

namespace cft
{
	TurbulenceForceField::TurbulenceForceField(float strength, RandomNumberGenerator& randomNumberGenerator) :
		m_strength(strength),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	MotionAcceleration TurbulenceForceField::evaluate(const MotionState& motionState) const
	{
		glm::vec3 direction = glm::normalize(m_randomNumberGenerator.generate(glm::vec3(-1.0f), glm::vec3(1.0f)));

		return MotionAcceleration{ direction * m_strength, glm::vec3(0.0f) };
	}
}