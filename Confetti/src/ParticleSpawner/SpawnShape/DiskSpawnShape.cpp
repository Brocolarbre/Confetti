#include "Confetti/ParticleSpawner/SpawnShape/DiskSpawnShape.hpp"

#include <glm/gtc/constants.hpp>

namespace cft
{
	SpawnContext DiskSpawnShape::generateValue(unsigned int count, unsigned int index) const
	{
		constexpr float goldenAngle = 2.39996323f;
		constexpr float twoPi = glm::two_pi<float>();
		
		float t = static_cast<float>(index) / static_cast<float>(count - 1);
	
		float angle = goldenAngle * static_cast<float>(index);
		float radius = m_radius * glm::sqrt(t);

		glm::vec3 tangent = glm::abs(m_axis.y) < 0.999f ? glm::normalize(glm::cross(m_axis, glm::vec3(0.0f, 1.0f, 0.0f))) : glm::normalize(glm::cross(m_axis, glm::vec3(1.0f, 0.0f, 0.0f)));
		glm::vec3 bitangent = glm::cross(m_axis, tangent);

		glm::vec3 position = (glm::cos(angle) * tangent + glm::sin(angle) * bitangent) * radius;
		glm::vec3 normal = glm::normalize(position);

		return SpawnContext{ position, normal };
	}

	DiskSpawnShape::DiskSpawnShape(float radius, const glm::vec3& axis) :
		m_radius(glm::max(radius, 0.0001f)),
		m_axis(glm::normalize(axis))
	{

	}

	std::unique_ptr<SpawnShape> DiskSpawnShape::clone() const
	{
		return std::make_unique<DiskSpawnShape>(*this);
	}
}