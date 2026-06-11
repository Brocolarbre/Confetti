#pragma once

#include "SpawnShape.hpp"

namespace cft
{
	class CircleSpawnShape : public SpawnShape
	{
	private:
		float m_radius;
		glm::vec3 m_axis;

		SpawnContext generateValue(unsigned int count, unsigned int index) const override;

	public:
		CircleSpawnShape(float radius, const glm::vec3& axis);

		virtual std::unique_ptr<SpawnShape> clone() const override;
	};
}