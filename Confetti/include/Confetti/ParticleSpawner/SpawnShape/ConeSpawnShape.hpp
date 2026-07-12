#pragma once

#include "SpawnShape.hpp"

namespace cft
{
	class ConeSpawnShape : public CloneableSpawnShape<ConeSpawnShape>
	{
	private:
		float m_height;
		float m_radius;
		glm::vec3 m_axis;

		SpawnContext generateValue(unsigned int count, unsigned int index) const override;

	public:
		ConeSpawnShape(float height, float radius, const glm::vec3& axis);
	};
}