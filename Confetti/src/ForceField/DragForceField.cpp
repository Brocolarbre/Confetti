#include "Confetti/ForceField/DragForceField.hpp"

namespace cft
{
	DragForceField::DragForceField(float strength) :
		m_strength(strength)
	{

	}

	std::unique_ptr<ForceField> DragForceField::clone() const
	{
		return std::make_unique<DragForceField>(*this);
	}

	glm::vec3 DragForceField::apply(float elapsedTime, const Transform& transform) const
	{
		return -glm::max(glm::vec3(m_strength), glm::vec3(0.0f));
	}
}