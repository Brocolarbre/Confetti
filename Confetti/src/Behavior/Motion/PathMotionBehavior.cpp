#include "Confetti/Behavior/Motion/PathMotionBehavior.hpp"

namespace cft
{
	PathMotionBehavior::PathMotionBehavior(lw::Curve path, std::unique_ptr<lw::Interpolator> interpolator, std::unique_ptr<lw::Easing> easing, float speed) :
		m_path(std::move(path)),
		m_interpolator(std::move(interpolator)),
		m_easing(std::move(easing)),
		m_speed(speed)
	{
		
	}

	PathMotionBehavior::PathMotionBehavior(const PathMotionBehavior& pathMotionBehavior) :
		m_path(pathMotionBehavior.m_path),
		m_interpolator(pathMotionBehavior.m_interpolator->clone()),
		m_easing(pathMotionBehavior.m_easing ? pathMotionBehavior.m_easing->clone() : nullptr),
		m_speed(pathMotionBehavior.m_speed)
	{

	}

	glm::vec3 PathMotionBehavior::evaluate(float age, const MotionState& motionState)
	{
		float t = m_easing ? m_easing->operator()(age * m_speed) : age * m_speed;
		lw::Point point = m_interpolator->operator()(m_path, t);
		return glm::vec3(point.x, point.y, point.z);
	}
}