#pragma once

#include "ForceField.hpp"
#include "SpatialInfluence.hpp"

namespace cft
{
	class ShockWaveForceField : public ForceField
	{
	private:
		SpatialInfluence m_spatialInfluence;
		glm::vec3 m_axis;
		float m_speed;
		float m_strength;
		float m_thickness;

	public:
		ShockWaveForceField(const SpatialInfluence& spatialInfluence, const glm::vec3& axis, float speed, float strength, float thickness);

		std::unique_ptr<ForceField> clone() const override;
		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}