#include "Confetti/ForceField/TurbulenceForceField.hpp"

namespace cft
{
	TurbulenceForceField::TurbulenceForceField(float strength, RandomNumberGenerator& randomNumberGenerator) :
		m_strength(strength),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	std::unique_ptr<ForceField> TurbulenceForceField::clone() const
	{
		return std::make_unique<TurbulenceForceField>(*this);
	}

	glm::vec3 TurbulenceForceField::apply(float elapsedTime, const Transform& transform) const
	{
		glm::vec3 direction = glm::normalize(m_randomNumberGenerator.generate(glm::vec3(-1.0f), glm::vec3(1.0f)));

		return direction * m_strength;
	}
}