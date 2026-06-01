#pragma once

#include "ForceField.hpp"
#include "SpatialInfluence.hpp"

namespace cft
{
	class VortexForceField : public ForceField
	{
	private:
		SpatialInfluence m_spatialInfluence;
		glm::vec3 m_axis;
		float m_strength;
		float m_pullStrength;

	public:
		VortexForceField(const SpatialInfluence& spatialInfluence, const glm::vec3& axis, float strength, float pullStrength);

		std::unique_ptr<ForceField> clone() const override;
		glm::vec3 apply(float elapsedTime, const Transform& transform) const override;
	};
}