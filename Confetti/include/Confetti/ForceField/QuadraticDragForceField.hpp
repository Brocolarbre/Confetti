#pragma once

#include "ForceField.hpp"

namespace cft
{
	class QuadraticDragForceField : public ForceField
	{
	private:
		float m_strength;

	public:
		QuadraticDragForceField(float strength);

		std::unique_ptr<ForceField> clone() const override;
		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}