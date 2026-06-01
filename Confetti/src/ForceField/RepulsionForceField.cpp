#include "Confetti/ForceField/RepulsionForceField.hpp"

namespace cft
{
	RepulsionForceField::RepulsionForceField(const SpatialInfluence& spatialInfluence, float strength) :
		m_spatialInfluence(spatialInfluence),
		m_strength(strength)
	{

	}

	std::unique_ptr<ForceField> RepulsionForceField::clone() const
	{
		return std::make_unique<RepulsionForceField>(*this);
	}

	glm::vec3 RepulsionForceField::apply(float elapsedTime, const Transform& transform) const
	{
		float strengthFactor = m_spatialInfluence.getStrengthFactor(transform.position);
		glm::vec3 offset = transform.position - m_spatialInfluence.getOrigin();

		glm::vec3 direction = glm::normalize(offset);
		return direction * m_strength * strengthFactor;
	}
}