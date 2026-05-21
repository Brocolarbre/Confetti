#include "ConfettiEngine/ForceField/AttenuationForceField.hpp"

namespace cft
{
	AttenuationForceField::AttenuationForceField(const glm::vec3& origin, float radius, float strength) :
		m_origin(origin),
		m_radius(radius),
		m_strength(strength)
	{

	}

	glm::vec3 AttenuationForceField::apply(const glm::vec3& velocity, const glm::vec3& position, float elapsedTime, float deltaTime) const
	{
		float squaredRadius = m_radius * m_radius; // Code duplication
		glm::vec3 offset = m_origin - position;
		float squaredDistance = glm::dot(offset, offset);
		float strengthContribution = 1.0f - glm::clamp(squaredDistance / squaredRadius, 0.0f, 1.0f);

		return glm::max(velocity - m_strength * strengthContribution, glm::vec3(0.0f));
	}
}