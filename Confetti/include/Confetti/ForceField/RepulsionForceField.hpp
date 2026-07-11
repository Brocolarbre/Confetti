#pragma once

#include "ForceField.hpp"
#include "SpatialInfluence.hpp"

namespace cft
{
	class RepulsionForceField : public ForceField
	{
		SpatialInfluence m_spatialInfluence;
		float m_strength;

	public:
		RepulsionForceField(const SpatialInfluence& spatialInfluence, float strength);

		std::unique_ptr<ForceField> clone() const override;
		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}