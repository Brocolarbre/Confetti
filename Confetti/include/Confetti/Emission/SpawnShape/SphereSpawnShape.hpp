#pragma once

#include "SpawnShape.hpp"

namespace cft
{
	class SphereSpawnShape : public Cloneable<SphereSpawnShape, SpawnShape>
	{
	private:
		float m_radius;

		SpawnContext generateValue(unsigned int count, unsigned int index) const override;

	public:
		SphereSpawnShape(float radius);
	};
}