#include "Confetti/ForceField/VortexForceField.hpp"

namespace cft
{
	VortexForceField::VortexForceField(const SpatialInfluence& spatialInfluence, const glm::vec3& axis, float strength, float pullStrength) :
		m_spatialInfluence(spatialInfluence),
		m_axis(glm::normalize(axis)),
		m_strength(strength),
		m_pullStrength(pullStrength)
	{

	}

	std::unique_ptr<ForceField> VortexForceField::clone() const
	{
		return std::make_unique<VortexForceField>(*this);
	}

	glm::vec3 VortexForceField::apply(float elapsedTime, const Transform& transform) const
	{
		float strengthFactor = m_spatialInfluence.getStrengthFactor(transform.position);

		if (strengthFactor == 0.0f)
			return glm::vec3(0.0f);

		glm::vec3 offset = transform.position - m_spatialInfluence.getOrigin();
		glm::vec3 radial = offset - m_axis * glm::dot(offset, m_axis);

		float radialLengthSquared = glm::dot(radial, radial);
		if (radialLengthSquared < 0.000001f)
			return glm::vec3(0.0f);

		glm::vec3 radialDirection = glm::normalize(radial);
		glm::vec3 tangent = glm::cross(m_axis, radialDirection);

		float radialDistance = glm::sqrt(radialLengthSquared);
		float spinFactor = 1.0f / glm::max(radialDistance, 0.1f);
		glm::vec3 inward = -radialDirection;

		return (tangent * m_strength + inward * m_pullStrength) * strengthFactor * spinFactor;
	}
}