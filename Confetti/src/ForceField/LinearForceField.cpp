#include "Confetti/ForceField/LinearForceField.hpp"

namespace cft
{
	LinearForceField::LinearForceField(const glm::vec3& direction, float strength) :
		m_direction(direction),
		m_strength(strength)
	{

	}

	std::unique_ptr<ForceField> LinearForceField::clone() const
	{
		return std::make_unique<LinearForceField>(*this);
	}

	glm::vec3 LinearForceField::apply(const glm::vec3& position, float elapsedTime, float deltaTime) const
	{
		return m_direction * m_strength * deltaTime;
	}
}