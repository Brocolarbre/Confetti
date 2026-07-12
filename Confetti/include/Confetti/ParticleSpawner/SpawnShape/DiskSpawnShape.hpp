#pragma once

#include "SpawnShape.hpp"

namespace cft
{
	class DiskSpawnShape : public Cloneable<DiskSpawnShape, SpawnShape>
	{
	private:
		float m_radius;
		glm::vec3 m_axis;

		SpawnContext generateValue(unsigned int count, unsigned int index) const override;

	public:
		DiskSpawnShape(float radius, const glm::vec3& axis);
	};
}