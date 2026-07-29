#include "Confetti/Behavior/Motion/JitterMotionBehavior.hpp"

namespace cft
{
	JitterMotionBehavior::JitterMotionBehavior(float strength, std::uint64_t seed) :
		m_strength(strength),
		m_randomNumberGenerator(seed)
	{

	}

	std::optional<std::uint64_t> JitterMotionBehavior::getSeed() const
	{
		return m_randomNumberGenerator.getSeed();
	}

	void JitterMotionBehavior::setSeed(std::uint64_t seed)
	{
		m_randomNumberGenerator.setSeed(seed);
	}

	glm::vec3 JitterMotionBehavior::evaluate(float age, const MotionState& motionState)
	{
		return m_randomNumberGenerator.generate(glm::vec3(-m_strength), glm::vec3(m_strength));
	}
}