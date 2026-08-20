#pragma once

#include "SpawnShape.hpp"

namespace cft
{
	class CONFETTI_API SpiralSpawnShape : public Cloneable<SpiralSpawnShape, SpawnShape>
	{
	private:
		float m_height;
		float m_radius;
		float m_turns;
		bool m_helix;
		glm::vec3 m_axis;

		SpawnContext generateValue(unsigned int count, unsigned int index) const override;

	public:
		SpiralSpawnShape(float height, float radius, float turns, bool helix, const glm::vec3& axis);
	};
}