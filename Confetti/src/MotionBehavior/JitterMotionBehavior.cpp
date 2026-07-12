#include "Confetti/MotionBehavior/JitterMotionBehavior.hpp"

namespace cft
{
	JitterMotionBehavior::JitterMotionBehavior(float strength, RandomNumberGenerator& randomNumberGenerator) :
		m_strength(strength),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	glm::vec3 JitterMotionBehavior::evaluate(float elapsedTime, const MotionState& motionState)
	{
		return m_randomNumberGenerator.generate(glm::vec3(-m_strength), glm::vec3(m_strength));
	}
}