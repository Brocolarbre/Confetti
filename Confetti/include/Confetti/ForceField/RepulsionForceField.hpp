#pragma once

#include "ForceField.hpp"
#include "SpatialInfluence.hpp"

namespace cft
{
	class RepulsionForceField : public Cloneable<RepulsionForceField, ForceField>
	{
		SpatialInfluence m_spatialInfluence;
		float m_strength;

	public:
		RepulsionForceField(const SpatialInfluence& spatialInfluence, float strength);

		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}