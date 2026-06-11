#pragma once

#include "SpawnShape.hpp"

namespace cft
{
	class CylinderSpawnShape : public SpawnShape
	{
	private:
		float m_height;
		float m_radius;
		glm::vec3 m_axis;

		SpawnContext generateValue(unsigned int count, unsigned int index) const override;

	public:
		CylinderSpawnShape(float height, float radius, const glm::vec3& axis);

		virtual std::unique_ptr<SpawnShape> clone() const override;
	};
}