#pragma once

#include "ForceField.hpp"
#include "SpatialInfluence.hpp"

namespace cft
{
	class AttractionForceField : public Cloneable<AttractionForceField, ForceField>
	{
	private:
		SpatialInfluence m_spatialInfluence;
		float m_strength;

	public:
		AttractionForceField(const SpatialInfluence& spatialInfluence, float strength);

		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}