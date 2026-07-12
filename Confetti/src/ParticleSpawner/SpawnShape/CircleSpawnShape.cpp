#include "Confetti/ParticleSpawner/SpawnShape/CircleSpawnShape.hpp"

#include <glm/gtc/constants.hpp>

namespace cft
{
	SpawnContext CircleSpawnShape::generateValue(unsigned int count, unsigned int index) const
	{
		constexpr float twoPi = glm::two_pi<float>();
		float t = static_cast<float>(index) / static_cast<float>(count - 1);
		float angle = twoPi * t;
		
		glm::vec3 tangent = glm::abs(m_axis.y) < 0.999f ? glm::normalize(glm::cross(m_axis, glm::vec3(0.0f, 1.0f, 0.0f))) : glm::normalize(glm::cross(m_axis, glm::vec3(1.0f, 0.0f, 0.0f)));
		glm::vec3 bitangent = glm::cross(m_axis, tangent);

		glm::vec3 position = (glm::cos(angle) * tangent + glm::sin(angle) * bitangent) * m_radius;
		glm::vec3 normal = glm::normalize(position);

		return SpawnContext{ position, normal };
	}

	CircleSpawnShape::CircleSpawnShape(float radius, const glm::vec3& axis) :
		m_radius(glm::max(radius, 0.0001f)),
		m_axis(glm::normalize(axis))
	{

	}
}