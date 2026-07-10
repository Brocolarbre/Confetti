#pragma once

#include "MotionBehavior.hpp"

namespace cft
{
	class SegmentMotionBehavior : public MotionBehavior
	{
	private:
		glm::vec3 m_from;
		glm::vec3 m_to;
		float m_speed;

	public:
		SegmentMotionBehavior(const glm::vec3& from, const glm::vec3& to, float speed);

		std::unique_ptr<MotionBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, Transform& transform) override;
	};
}