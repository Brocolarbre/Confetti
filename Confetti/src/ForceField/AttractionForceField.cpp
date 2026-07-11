#include "Confetti/ForceField/AttractionForceField.hpp"

namespace cft
{
	AttractionForceField::AttractionForceField(const SpatialInfluence& spatialInfluence, float strength) :
		m_spatialInfluence(spatialInfluence),
		m_strength(strength)
	{

	}

	std::unique_ptr<ForceField> AttractionForceField::clone() const
	{
		return std::make_unique<AttractionForceField>(*this);
	}

	MotionAcceleration AttractionForceField::evaluate(const MotionState& motionState) const
	{
		float strengthFactor = m_spatialInfluence.getStrengthFactor(motionState.position);
		glm::vec3 offset = m_spatialInfluence.getOrigin() - motionState.position;

		glm::vec3 direction = glm::normalize(offset);
		return MotionAcceleration{ direction * m_strength * strengthFactor, glm::vec3(0.0f) };
	}
}