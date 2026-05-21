#include "Confetti/ForceField/RepulsionForceField.hpp"

namespace cft
{
	RepulsionForceField::RepulsionForceField(const glm::vec3& origin, float radius, float strength) :
		m_origin(origin),
		m_radius(radius),
		m_strength(strength)
	{

	}

	glm::vec3 RepulsionForceField::apply(const glm::vec3& velocity, const glm::vec3& position, float elapsedTime, float deltaTime) const
	{
		float squaredRadius = m_radius * m_radius;
		glm::vec3 offset = position - m_origin;
		float squaredDistance = glm::dot(offset, offset);
		float strengthContribution = 1.0f - glm::clamp(squaredDistance / squaredRadius, 0.0f, 1.0f);

		glm::vec3 direction = glm::normalize(offset);
		return velocity + direction * m_strength * strengthContribution * deltaTime;
	}
}