#include "Confetti/ForceField/JitterForceField.hpp"

namespace cft
{
	JitterForceField::JitterForceField(float strength, RandomNumberGenerator& randomNumberGenerator) :
		m_strength(strength),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	std::unique_ptr<ForceField> JitterForceField::clone() const
	{
		return std::make_unique<JitterForceField>(*this);
	}

	glm::vec3 JitterForceField::apply(float elapsedTime, const Transform& transform) const
	{
		glm::vec3 direction = glm::normalize(m_randomNumberGenerator.generate(glm::vec3(-1.0f), glm::vec3(1.0f)));

		return direction * m_strength;
	}
}