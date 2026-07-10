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

	void JitterMotionBehavior::update(float elapsedTime, float deltaTime, Transform& transform)
	{
		transform.position += m_randomNumberGenerator.generate(-m_strength, m_strength) * deltaTime;
	}
}