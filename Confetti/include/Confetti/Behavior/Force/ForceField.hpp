#pragma once

#include "Confetti/Data/MotionState.hpp"
#include "Confetti/Tool/Cloneable.hpp"

namespace cft
{
	struct MotionAcceleration
	{
		glm::vec3 linear;
		glm::vec3 angular;
	};

	class ForceField
	{
	public:
		virtual ~ForceField() = default;

		virtual std::unique_ptr<ForceField> clone() const = 0;
		virtual MotionAcceleration evaluate(const MotionState& motionState) const = 0;
	};
}