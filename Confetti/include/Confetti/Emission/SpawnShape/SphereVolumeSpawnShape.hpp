#pragma once

#include "SpawnShape.hpp"

namespace cft
{
	class CONFETTI_API SphereVolumeSpawnShape : public Cloneable<SphereVolumeSpawnShape, SpawnShape>
	{
	private:
		float m_radius;

		SpawnContext generateValue(unsigned int count, unsigned int index) const override;

	public:
		SphereVolumeSpawnShape(float radius);
	};
}