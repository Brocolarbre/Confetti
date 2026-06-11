#include "Confetti/ParticleSpawner/SpawnShape/ConeSpawnShape.hpp"

#include <glm/gtc/constants.hpp>

namespace cft
{
	SpawnContext ConeSpawnShape::generateValue(unsigned int count, unsigned int index) const
	{
		constexpr float goldenAngle = 2.39996323f;

		float t = static_cast<float>(index) / static_cast<float>(count - 1);
		float currentHeight = t * m_height;
		float currentRadius = (currentHeight / m_height) * m_radius;
		float angle = index * goldenAngle;

		glm::vec3 tangent = glm::abs(m_axis.y) < 0.999f ? glm::normalize(glm::cross(m_axis, glm::vec3(0.0f, 1.0f, 0.0f))) : glm::normalize(glm::cross(m_axis, glm::vec3(1.0f, 0.0f, 0.0f)));
		glm::vec3 bitangent = glm::cross(m_axis, tangent);

		glm::vec3 radial = glm::cos(angle) * tangent + glm::sin(angle) * bitangent;

		glm::vec3 position = m_axis * currentHeight + radial * currentRadius;
		glm::vec3 normal = glm::normalize(radial * m_height - m_axis * m_radius);

		return SpawnContext{ position, normal };
	}

	ConeSpawnShape::ConeSpawnShape(float height, float radius, const glm::vec3& axis) :
		m_height(height),
		m_radius(glm::max(radius, 0.0001f)),
		m_axis(glm::normalize(axis))
	{

	}

	std::unique_ptr<SpawnShape> ConeSpawnShape::clone() const
	{
		return std::make_unique<ConeSpawnShape>(*this);
	}
}