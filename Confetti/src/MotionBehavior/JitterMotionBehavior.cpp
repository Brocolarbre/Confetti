#include "Confetti/MotionBehavior/JitterMotionBehavior.hpp"

namespace cft
{
	JitterMotionBehavior::JitterMotionBehavior(float strength, RandomNumberGenerator& randomNumberGenerator) :
		m_strength(strength),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	std::unique_ptr<MotionBehavior> JitterMotionBehavior::clone() const
	{
		return std::make_unique<JitterMotionBehavior>(*this);
	}

	glm::vec3 JitterMotionBehavior::evaluate(float elapsedTime, const MotionState& motionState)
	{
		return m_randomNumberGenerator.generate(glm::vec3(-m_strength), glm::vec3(m_strength));
	}
}