#pragma once

#include "MotionBehavior.hpp"

namespace cft
{
	class VibrationMotionBehavior : public MotionBehavior
	{
	public:
		std::unique_ptr<MotionBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, Transform& transform) override;
	};
}