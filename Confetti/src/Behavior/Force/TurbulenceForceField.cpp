#include "Confetti/Behavior/Force/TurbulenceForceField.hpp"

namespace cft
{
	TurbulenceForceField::TurbulenceForceField(float strength, std::uint64_t seed) :
		m_strength(strength),
		m_randomNumberGenerator(seed)
	{

	}

	std::optional<std::uint64_t> TurbulenceForceField::getSeed() const
	{
		return m_randomNumberGenerator.getSeed();
	}

	void TurbulenceForceField::setSeed(std::uint64_t seed)
	{
		m_randomNumberGenerator.setSeed(seed);
	}

	MotionAcceleration TurbulenceForceField::evaluate(const MotionState& motionState)
	{
		glm::vec3 direction = glm::normalize(m_randomNumberGenerator.generate(glm::vec3(-1.0f), glm::vec3(1.0f)));

		return MotionAcceleration{ direction * m_strength, glm::vec3(0.0f) };
	}
}