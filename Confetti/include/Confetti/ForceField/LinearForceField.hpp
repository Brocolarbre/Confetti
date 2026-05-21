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

		glm::vec3 apply(const glm::vec3& velocity, const glm::vec3& position, float elapsedTime, float deltaTime) const override;
	};
}