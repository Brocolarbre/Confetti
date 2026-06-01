#pragma once

#include "ForceField.hpp"

namespace cft
{
	class LinearForceField : public ForceField
	{
	private:
		glm::vec3 m_direction;
		float m_strength;

	public:
		LinearForceField(const glm::vec3& direction, float strength);

		std::unique_ptr<ForceField> clone() const override;
		glm::vec3 apply(float elapsedTime, float deltaTime, const Transform& transform) const override;
	};
}