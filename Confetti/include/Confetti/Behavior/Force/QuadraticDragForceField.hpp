#pragma once

#include "ForceField.hpp"

namespace cft
{
	class QuadraticDragForceField : public Cloneable<QuadraticDragForceField, ForceField>
	{
	private:
		float m_strength;

	public:
		QuadraticDragForceField(float strength);

		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}