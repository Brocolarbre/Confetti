#pragma once

#include "ForceField.hpp"

namespace cft
{
	class AttractionForceField : public ForceField
	{
	private:
		glm::vec3 m_origin;
		float m_radius;
		float m_strength;

	public:
		AttractionForceField(const glm::vec3& origin, float radius, float strength);

		std::unique_ptr<ForceField> clone() const override;
		glm::vec3 apply(float elapsedTime, float deltaTime, const Transform& transform) const override;
	};
}