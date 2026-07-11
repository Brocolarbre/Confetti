#pragma once

#include "Confetti/Particle/MotionState.hpp"

#include <memory>

namespace cft
{
	class MotionBehavior
	{
	public:
		virtual ~MotionBehavior() = default;

		virtual std::unique_ptr<MotionBehavior> clone() const = 0;
		virtual glm::vec3 evaluate(float elapsedTime, const MotionState& motionState) = 0;
	};
}