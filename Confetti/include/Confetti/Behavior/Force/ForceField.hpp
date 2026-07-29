#pragma once

#include "Confetti/Export.hpp"
#include "Confetti/Data/MotionState.hpp"
#include "Confetti/Tool/Cloneable.hpp"
#include "Confetti/Tool/Seedable.hpp"

namespace cft
{
	struct MotionAcceleration
	{
		glm::vec3 linear;
		glm::vec3 angular;
	};

	class CONFETTI_API ForceField : public Seedable
	{
	public:
		virtual ~ForceField() = default;

		virtual std::unique_ptr<ForceField> clone() const = 0;

		virtual MotionAcceleration evaluate(const MotionState& motionState) = 0;
	};
}