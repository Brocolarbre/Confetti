#pragma once

#include "ForceField.hpp"
#include "SpatialInfluence.hpp"

namespace cft
{
	class AttractionForceField : public ForceField
	{
	private:
		SpatialInfluence m_spatialInfluence;
		float m_strength;

	public:
		AttractionForceField(const SpatialInfluence& spatialInfluence, float strength);

		std::unique_ptr<ForceField> clone() const override;
		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}