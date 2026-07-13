#pragma once

#include "MotionBehavior.hpp"

namespace cft
{
	class SpiralMotionBehavior : public Cloneable<SpiralMotionBehavior, MotionBehavior>
	{
	private:
		glm::vec3 m_origin;
		glm::vec3 m_axis;
		float m_startRadius;
		float m_growth;
		float m_speed;
		float m_rise;

		glm::vec3 m_tangent;
		glm::vec3 m_bitangent;

	public:
		SpiralMotionBehavior(const glm::vec3& origin, const glm::vec3& axis, float startRadius, float growth, float speed, float rise);

		glm::vec3 evaluate(float age, const MotionState& motionState) override;
	};
}