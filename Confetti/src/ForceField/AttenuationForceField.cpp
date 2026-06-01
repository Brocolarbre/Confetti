#include "Confetti/ForceField/AttenuationForceField.hpp"

namespace cft
{
	AttenuationForceField::AttenuationForceField(const glm::vec3& origin, float radius, float strength) :
		m_origin(origin),
		m_radius(radius),
		m_strength(strength)
	{

	}

	std::unique_ptr<ForceField> AttenuationForceField::clone() const
	{
		return std::make_unique<AttenuationForceField>(*this);
	}

	glm::vec3 AttenuationForceField::apply(float elapsedTime, float deltaTime, const Transform& transform) const
	{
		float squaredRadius = m_radius * m_radius; // Code duplication
		glm::vec3 offset = m_origin - transform.position;
		float squaredDistance = glm::dot(offset, offset);
		float strengthContribution = 1.0f - glm::clamp(squaredDistance / squaredRadius, 0.0f, 1.0f);

		return -glm::max(glm::vec3(m_strength) * strengthContribution, glm::vec3(0.0f));
	}
}