#include "Confetti/Behavior/Force/ShockWaveForceField.hpp"

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

	MotionAcceleration ShockWaveForceField::evaluate(const MotionState& motionState) const
	{
		float spatialFactor = m_spatialInfluence.getStrengthFactor(motionState.position);

		if (spatialFactor == 0.0f)
			return MotionAcceleration{ glm::vec3(0.0f), glm::vec3(0.0f) };

		float waveRadius = m_speed;

		glm::vec3 offset = motionState.position - m_spatialInfluence.getOrigin();
		glm::vec3 radial = offset - m_axis * glm::dot(offset, m_axis);

		float radialLengthSquared = glm::dot(radial, radial);

		if (radialLengthSquared < 0.000001f)
			return MotionAcceleration{ glm::vec3(0.0f), glm::vec3(0.0f) };

		float radialDistance = glm::sqrt(radialLengthSquared);

		glm::vec3 radialDirection = radial / radialDistance;
		float distanceToWave = radialDistance - waveRadius;

		float sigma = m_thickness;
		float gaussian = glm::exp(-(distanceToWave * distanceToWave) / (2.0f * sigma * sigma));

		return MotionAcceleration{ radialDirection * m_strength * gaussian * spatialFactor, glm::vec3(0.0f) };
	}
}