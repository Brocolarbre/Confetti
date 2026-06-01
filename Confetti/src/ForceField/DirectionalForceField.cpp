#include "Confetti/ForceField/DirectionalForceField.hpp"

namespace cft
{
	DirectionalForceField::DirectionalForceField(const glm::vec3& direction, float strength) :
		m_direction(direction),
		m_strength(strength)
	{

	}

	std::unique_ptr<ForceField> DirectionalForceField::clone() const
	{
		return std::make_unique<DirectionalForceField>(*this);
	}

	glm::vec3 DirectionalForceField::apply(float elapsedTime, const Transform& transform) const
	{
		return m_direction * m_strength;
	}
}