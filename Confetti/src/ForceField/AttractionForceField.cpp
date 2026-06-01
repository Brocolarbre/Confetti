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

	glm::vec3 AttractionForceField::apply(float elapsedTime, const Transform& transform) const
	{
		float strengthFactor = m_spatialInfluence.getStrengthFactor(transform.position);
		glm::vec3 offset = m_spatialInfluence.getOrigin() - transform.position;

		glm::vec3 direction = glm::normalize(offset);
		return direction * m_strength * strengthFactor;
	}
}