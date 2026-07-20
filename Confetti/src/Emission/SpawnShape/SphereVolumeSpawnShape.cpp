#include "Confetti/Emission/SpawnShape/SphereVolumeSpawnShape.hpp"

namespace cft
{
	SpawnContext SphereVolumeSpawnShape::generateValue(unsigned int count, unsigned int index) const
	{
		constexpr float goldenAngle = 2.39996323f;

		float u = (index + 0.5f) / count;
		float y = 1.0f - 2.0f * u;
		float r = glm::sqrt(1.0f - y * y);

		float yaw = index * goldenAngle;

		glm::vec3 direction(r * glm::cos(yaw), y, r * glm::sin(yaw));
		float radius = m_radius * glm::pow(u, 1.0f / 3.0f);

		return SpawnContext{ direction * radius, glm::normalize(direction) };
	}

	SphereVolumeSpawnShape::SphereVolumeSpawnShape(float radius) :
		m_radius(radius)
	{

	}
}