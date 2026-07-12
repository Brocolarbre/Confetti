#pragma once

#include "ForceField.hpp"

namespace cft
{
	class LinearDragForceField : public CloneableForceField<LinearDragForceField>
	{
	private:
		float m_strength;

	public:
		LinearDragForceField(float strength);

		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}