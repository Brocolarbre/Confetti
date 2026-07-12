#pragma once

#include "MotionBehavior.hpp"

#include <LineWeaver/Interpolation/Interpolator.hpp>
#include <LineWeaver/Easing/Easing.hpp>
#include <optional>

namespace cft
{
	class PathMotionBehavior : public Cloneable<PathMotionBehavior, MotionBehavior>
	{
	private:
		lw::Curve m_path;
		std::unique_ptr<lw::Interpolator> m_interpolator;
		std::unique_ptr<lw::Easing> m_easing;
		float m_speed;

	public:
		PathMotionBehavior(lw::Curve path, std::unique_ptr<lw::Interpolator> interpolator, std::unique_ptr<lw::Easing> easing, float speed);
		PathMotionBehavior(const PathMotionBehavior& pathMotionBehavior);

		glm::vec3 evaluate(float elapsedTime, const MotionState& motionState) override;
	};
}