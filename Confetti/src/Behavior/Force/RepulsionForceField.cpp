#include "Confetti/Behavior/Force/RepulsionForceField.hpp"

namespace cft
{
	RepulsionForceField::RepulsionForceField(const SpatialInfluence& spatialInfluence, float strength) :
		m_spatialInfluence(spatialInfluence),
		m_strength(strength)
	{

	}

	MotionAcceleration RepulsionForceField::evaluate(const MotionState& motionState) const
	{
		float strengthFactor = m_spatialInfluence.getStrengthFactor(motionState.position);
		glm::vec3 offset = motionState.position - m_spatialInfluence.getOrigin();

		glm::vec3 direction = glm::normalize(offset);
		return MotionAcceleration{ direction * m_strength * strengthFactor, glm::vec3(0.0f) };
	}
}