#include "Confetti/ForceField/ShockWaveForceField.hpp"

namespace cft
{
	ShockWaveForceField::ShockWaveForceField(const SpatialInfluence& spatialInfluence, const glm::vec3& axis, float speed, float strength, float thickness) :
		m_spatialInfluence(spatialInfluence),
		m_axis(glm::normalize(axis)),
		m_speed(speed),
		m_strength(strength),
		m_thickness(glm::max(thickness, 0.0001f))
	{

	}

	std::unique_ptr<ForceField> ShockWaveForceField::clone() const
	{
		return std::make_unique<ShockWaveForceField>(*this);
	}

	glm::vec3 ShockWaveForceField::apply(float elapsedTime, const Transform& transform) const
	{
		float spatialFactor = m_spatialInfluence.getStrengthFactor(transform.position);

		if (spatialFactor == 0.0f)
			return glm::vec3(0.0f);

		float waveRadius = m_speed * elapsedTime;

		glm::vec3 offset = transform.position - m_spatialInfluence.getOrigin();
		glm::vec3 radial = offset - m_axis * glm::dot(offset, m_axis);

		float radialLengthSquared = glm::dot(radial, radial);

		if (radialLengthSquared < 0.000001f)
			return glm::vec3(0.0f);

		float radialDistance = glm::sqrt(radialLengthSquared);

		glm::vec3 radialDirection = radial / radialDistance;
		float distanceToWave = radialDistance - waveRadius;

		float sigma = m_thickness;
		float gaussian = glm::exp(-(distanceToWave * distanceToWave) / (2.0f * sigma * sigma));

		return radialDirection * m_strength * gaussian * spatialFactor;
	}
}