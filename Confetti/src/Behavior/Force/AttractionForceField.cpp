#include "Confetti/Behavior/Force/AttractionForceField.hpp"

namespace cft
{
	AttractionForceField::AttractionForceField(const SpatialInfluence& spatialInfluence, float strength) :
		m_spatialInfluence(spatialInfluence),
		m_strength(strength)
	{

	}

	MotionAcceleration AttractionForceField::evaluate(const MotionState& motionState) const
	{
		float strengthFactor = m_spatialInfluence.getStrengthFactor(motionState.position);
		glm::vec3 offset = m_spatialInfluence.getOrigin() - motionState.position;

		glm::vec3 direction = glm::normalize(offset);
		return MotionAcceleration{ direction * m_strength * strengthFactor, glm::vec3(0.0f) };
	}
}