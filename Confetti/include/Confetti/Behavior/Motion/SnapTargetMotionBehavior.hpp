#pragma once

#include "MotionBehavior.hpp"

#include <functional>

namespace cft
{
	class CONFETTI_API SnapTargetMotionBehavior : public Cloneable<SnapTargetMotionBehavior, MotionBehavior>
	{
	private:
		std::function<glm::vec3()> m_targetProvider;

	public:
		SnapTargetMotionBehavior(std::function<glm::vec3()> targetProvider);

		glm::vec3 evaluate(float age, const MotionState& motionState) override;
	};
}