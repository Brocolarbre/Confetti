#pragma once

#include "ForceField.hpp"

namespace cft
{
	class AttenuationForceField : public ForceField
	{
	private:
		glm::vec3 m_origin;
		float m_radius;
		float m_strength;

	public:
		AttenuationForceField(const glm::vec3& origin, float radius, float strength);

		glm::vec3 apply(const glm::vec3& velocity, const glm::vec3& position, float elapsedTime, float deltaTime) const override;
	};
}