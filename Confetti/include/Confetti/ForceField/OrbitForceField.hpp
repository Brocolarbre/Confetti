#pragma once

#include "ForceField.hpp"
#include "SpatialInfluence.hpp"

namespace cft
{
	class OrbitForceField : public CloneableForceField<OrbitForceField>
	{
	private:
		SpatialInfluence m_spatialInfluence;
		glm::vec3 m_axis;
		float m_strength;
		float m_radius;
		float m_radialCorrectionStrength;

	public:
		OrbitForceField(const SpatialInfluence& spatialInfluence, const glm::vec3& axis, float strength, float radius, float radialCorrectionStrength);

		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}