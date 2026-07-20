#pragma once

#include "ForceField.hpp"

namespace cft
{
	class LinearDragForceField : public Cloneable<LinearDragForceField, ForceField>
	{
	private:
		float m_strength;

	public:
		LinearDragForceField(float strength);

		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}