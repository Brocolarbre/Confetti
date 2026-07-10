#pragma once

#include "MotionBehavior.hpp"

namespace cft
{
	class WrapPositionMotionBehavior : public MotionBehavior
	{
	private:
		glm::vec3 m_minimumPosition;
		glm::vec3 m_maximumPosition;

	public:
		WrapPositionMotionBehavior(const glm::vec3& minimumPosition, const glm::vec3& maximumPosition);

		std::unique_ptr<MotionBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, Transform& transform) override;
	};
}