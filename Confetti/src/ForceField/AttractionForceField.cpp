#include "Confetti/ForceField/AttractionForceField.hpp"

namespace cft
{
	AttractionForceField::AttractionForceField(const glm::vec3& origin, float radius, float strength) :
		m_origin(origin),
		m_radius(radius),
		m_strength(strength)
	{

	}

	std::unique_ptr<ForceField> AttractionForceField::clone() const
	{
		return std::make_unique<AttractionForceField>(*this);
	}

	glm::vec3 AttractionForceField::apply(const glm::vec3& position, float elapsedTime, float deltaTime) const
	{
		float squaredRadius = m_radius * m_radius;
		glm::vec3 offset = m_origin - position;
		float squaredDistance = glm::dot(offset, offset);
		float strengthContribution = 1.0f - glm::clamp(squaredDistance / squaredRadius, 0.0f, 1.0f);

		glm::vec3 direction = glm::normalize(offset);
		return direction * m_strength * strengthContribution * deltaTime;
	}
}