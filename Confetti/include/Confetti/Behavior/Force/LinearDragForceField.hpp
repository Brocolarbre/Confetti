#pragma once

#include "ForceField.hpp"

namespace cft
{
	class CONFETTI_API LinearDragForceField : public Cloneable<LinearDragForceField, ForceField>
	{
	private:
		float m_strength;

	public:
		LinearDragForceField(float strength);

		MotionAcceleration evaluate(const MotionState& motionState) override;
	};
}