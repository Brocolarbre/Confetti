#pragma once

#include "MotionBehavior.hpp"

namespace cft
{
	class OrbitMotionBehavior : public MotionBehavior
	{
	private:
		glm::vec3 m_origin;
		glm::vec3 m_axis;
		float m_radius;
		float m_speed;

		glm::vec3 m_tangent;
		glm::vec3 m_bitangent;

	public:
		OrbitMotionBehavior(const glm::vec3& origin, const glm::vec3& axis, float radius, float speed);

		std::unique_ptr<MotionBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, Transform& transform) override;
	};
}