#include "Confetti/ParticleSpawner/SpawnShape/SphereSpawnShape.hpp"

namespace cft
{
	SpawnContext SphereSpawnShape::generateValue(unsigned int count, unsigned int index) const
	{
		constexpr float goldenAngle = 2.39996323f;

		float y = 1.0f - 2.0f * ((index + 0.5f) / count);
		float r = glm::sqrt(1.0f - y * y);

		float yaw = index * goldenAngle;

		glm::vec3 position(r * glm::cos(yaw), y, r * glm::sin(yaw));
		position *= m_radius;

		glm::vec3 normal = glm::normalize(position);

		return SpawnContext{ position, normal };
	}

	SphereSpawnShape::SphereSpawnShape(float radius) :
		m_radius(radius)
	{

	}
}