#include "Confetti/ForceField/RepulsionForceField.hpp"

namespace cft
{
	RepulsionForceField::RepulsionForceField(const glm::vec3& origin, float radius, float strength) :
		m_origin(origin),
		m_radius(radius),
		m_strength(strength)
	{

	}

	std::unique_ptr<ForceField> RepulsionForceField::clone() const
	{
		return std::make_unique<RepulsionForceField>(*this);
	}

	glm::vec3 RepulsionForceField::apply(float elapsedTime, float deltaTime, const Transform& transform) const
	{
		float squaredRadius = m_radius * m_radius;
		glm::vec3 offset = transform.position - m_origin;
		float squaredDistance = glm::dot(offset, offset);
		float strengthContribution = 1.0f - glm::clamp(squaredDistance / squaredRadius, 0.0f, 1.0f);

		glm::vec3 direction = glm::normalize(offset);
		return direction * m_strength * strengthContribution * deltaTime;
	}
}