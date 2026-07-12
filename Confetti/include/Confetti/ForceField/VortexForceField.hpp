#pragma once

#include "ForceField.hpp"
#include "SpatialInfluence.hpp"

namespace cft
{
	class VortexForceField : public CloneableForceField<VortexForceField>
	{
	private:
		SpatialInfluence m_spatialInfluence;
		glm::vec3 m_axis;
		float m_strength;
		float m_pullStrength;

	public:
		VortexForceField(const SpatialInfluence& spatialInfluence, const glm::vec3& axis, float strength, float pullStrength);

		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}