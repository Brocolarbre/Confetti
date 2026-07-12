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

	MotionAcceleration OrbitForceField::evaluate(const MotionState& motionState) const
	{
		float strengthFactor = m_spatialInfluence.getStrengthFactor(motionState.position);

		if (strengthFactor == 0.0f)
			return MotionAcceleration{ glm::vec3(0.0f), glm::vec3(0.0f) };

		glm::vec3 offset = motionState.position - m_spatialInfluence.getOrigin();
		glm::vec3 radial = offset - m_axis * glm::dot(offset, m_axis);

		float radialLengthSquared = glm::dot(radial, radial);
		if (radialLengthSquared < 0.000001f)
			return MotionAcceleration{ glm::vec3(0.0f), glm::vec3(0.0f) };

		glm::vec3 radialDirection = glm::normalize(radial);
		glm::vec3 tangent = glm::cross(m_axis, radialDirection);

		float currentRadius = glm::length(radial);
		float radiusError = m_radius - currentRadius;
		glm::vec3 correction = radialDirection + radiusError * m_radialCorrectionStrength;

		return MotionAcceleration{ (tangent * m_strength + correction) * strengthFactor, glm::vec3(0.0f) };
	}
}