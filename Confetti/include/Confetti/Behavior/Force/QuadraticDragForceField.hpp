#pragma once

#include "ForceField.hpp"

namespace cft
{
	class CONFETTI_API QuadraticDragForceField : public Cloneable<QuadraticDragForceField, ForceField>
	{
	private:
		float m_strength;

	public:
		QuadraticDragForceField(float strength);

		MotionAcceleration evaluate(const MotionState& motionState) override;
	};
}