#pragma once

#include "Confetti/Export.hpp"
#include "Confetti/Data/MotionState.hpp"
#include "Confetti/Tool/Cloneable.hpp"
#include "Confetti/Tool/Seedable.hpp"

namespace cft
{
	class CONFETTI_API MotionBehavior : public Seedable
	{
	public:
		virtual ~MotionBehavior() = default;

		virtual std::unique_ptr<MotionBehavior> clone() const = 0;

		virtual glm::vec3 evaluate(float age, const MotionState& motionState) = 0;
	};
}