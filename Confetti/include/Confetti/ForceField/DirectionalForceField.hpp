#pragma once

#include "ForceField.hpp"

namespace cft
{
	class DirectionalForceField : public ForceField
	{
	private:
		glm::vec3 m_direction;
		float m_strength;

	public:
		DirectionalForceField(const glm::vec3& direction, float strength);

		std::unique_ptr<ForceField> clone() const override;
		glm::vec3 apply(float elapsedTime, const Transform& transform) const override;
	};
}