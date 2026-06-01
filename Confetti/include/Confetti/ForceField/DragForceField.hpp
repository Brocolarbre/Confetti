#pragma once

#include "ForceField.hpp"

namespace cft
{
	class DragForceField : public ForceField
	{
	private:
		float m_strength;

	public:
		DragForceField(float strength);

		std::unique_ptr<ForceField> clone() const override;
		glm::vec3 apply(float elapsedTime, const Transform& transform) const override;
	};
}