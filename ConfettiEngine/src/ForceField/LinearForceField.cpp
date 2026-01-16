#include "ConfettiEngine/ForceField/LinearForceField.hpp"

namespace cft
{
	LinearForceField::LinearForceField(const glm::vec3& direction, float strength) :
		m_direction(direction),
		m_strength(strength)
	{

	}

	glm::vec3 LinearForceField::apply(const glm::vec3& velocity, const glm::vec3& position, float elapsedTime, float deltaTime) const
	{
		return velocity + m_direction * m_strength * deltaTime;
	}
}