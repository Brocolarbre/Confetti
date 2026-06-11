#include "Confetti/ParticleSpawner/SpawnShape/CylinderVolumeSpawnShape.hpp"

#include <glm/gtc/constants.hpp>

namespace cft
{
	SpawnContext CylinderVolumeSpawnShape::generateValue(unsigned int count, unsigned int index) const
	{
		constexpr float goldenAngle = 2.39996323f;

		float t = static_cast<float>(index) / static_cast<float>(count - 1);
		float currentHeight = t * m_height;
		float angle = index * goldenAngle;
		float radius = m_radius * glm::sqrt(static_cast<float>((index * 2654435761u) & 0xFFFF) / 65535.0f);


		glm::vec3 tangent = glm::abs(m_axis.y) < 0.999f ? glm::normalize(glm::cross(m_axis, glm::vec3(0.0f, 1.0f, 0.0f))) : glm::normalize(glm::cross(m_axis, glm::vec3(1.0f, 0.0f, 0.0f)));
		glm::vec3 bitangent = glm::cross(m_axis, tangent);

		glm::vec3 radial = glm::cos(angle) * tangent + glm::sin(angle) * bitangent;

		glm::vec3 position = m_axis * currentHeight + radial * radius;
		glm::vec3 normal = glm::normalize(radial);

		return SpawnContext{ position, normal };
	}

	CylinderVolumeSpawnShape::CylinderVolumeSpawnShape(float height, float radius, const glm::vec3& axis) :
		m_height(height),
		m_radius(glm::max(radius, 0.0001f)),
		m_axis(glm::normalize(axis))
	{

	}

	std::unique_ptr<SpawnShape> CylinderVolumeSpawnShape::clone() const
	{
		return std::make_unique<CylinderVolumeSpawnShape>(*this);
	}
}