#include "Confetti/ForceField/OrbitForceField.hpp"

namespace cft
{
	OrbitForceField::OrbitForceField(const SpatialInfluence& spatialInfluence, const glm::vec3& axis, float strength, float radius, float radialCorrectionStrength) :
		m_spatialInfluence(spatialInfluence),
		m_axis(glm::normalize(axis)),
		m_strength(strength),
		m_radius(radius),
		m_radialCorrectionStrength(radialCorrectionStrength)
	{

	}

	std::unique_ptr<ForceField> OrbitForceField::clone() const
	{
		return std::make_unique<OrbitForceField>(*this);
	}

	glm::vec3 OrbitForceField::apply(float elapsedTime, const Transform& transform) const
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

		float currentRadius = glm::length(radial);
		float radiusError = m_radius - currentRadius;
		glm::vec3 correction = radialDirection + radiusError * m_radialCorrectionStrength;

		return (tangent * m_strength + correction) * strengthFactor;
	}
}