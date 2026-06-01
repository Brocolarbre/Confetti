#pragma once

#include "Confetti/Particle/Transform.hpp"

#include <memory>

namespace cft
{
	class MotionBehavior
	{
	public:
		virtual ~MotionBehavior() = default;

		virtual std::unique_ptr<MotionBehavior> clone() const = 0;
		virtual void update(float elapsedTime, float deltaTime, Transform& transform) = 0;
	};
}