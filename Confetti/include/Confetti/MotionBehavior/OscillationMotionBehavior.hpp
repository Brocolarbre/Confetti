#pragma once

#include "MotionBehavior.hpp"

namespace cft
{
	class OscillationMotionBehavior : public Cloneable<OscillationMotionBehavior, MotionBehavior>
	{
	private:
		glm::vec3 m_from;
		glm::vec3 m_to;
		float m_speed;

	public:
		OscillationMotionBehavior(const glm::vec3& from, const glm::vec3& to, float speed);

		glm::vec3 evaluate(float elapsedTime, const MotionState& motionState) override;
	};
}