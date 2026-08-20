#pragma once

#include "SpawnShape.hpp"

namespace cft
{
	class CONFETTI_API GalaxyDiskSpawnShape : public Cloneable<GalaxyDiskSpawnShape, SpawnShape>
	{
	private:
		float m_radius;
		float m_bulgeRadius;
		float m_thickness;
		float m_turns;
		float m_armSpread;

		unsigned int m_arms;
		glm::vec3 m_axis;

		SpawnContext generateValue(unsigned int count, unsigned int index) const override;

	public:
		GalaxyDiskSpawnShape(float radius, float bulgeRadius, float thickness, unsigned int arms, float turns, float armSpread, const glm::vec3& axis);
	};
}