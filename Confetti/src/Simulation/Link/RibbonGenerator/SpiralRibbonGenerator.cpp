#include "Confetti/Simulation/Link/RibbonGenerator/SpiralRibbonGenerator.hpp"

namespace cft
{
	glm::vec3 SpiralRibbonGenerator::generateRibbonPoint(float t, float elapsedTime, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const
	{
		glm::vec3 a = fromParticle.postBehaviorPosition;
		glm::vec3 b = toParticle.postBehaviorPosition;

		glm::vec3 center = glm::mix(a, b, t);
		glm::vec3 axis = glm::normalize(b - a);

		glm::vec3 reference = glm::abs(axis.y) < 0.999f ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 right = glm::normalize(glm::cross(axis, reference));
		glm::vec3 up = glm::normalize(glm::cross(right, axis));
		
		float angle = t * m_frequency + elapsedTime * m_animationSpeed;
		glm::vec3 offset = (glm::cos(angle) * right + glm::sin(angle) * up) * m_radius;

		return center + offset;
	}

	SpiralRibbonGenerator::SpiralRibbonGenerator(float frequency, float radius, float animationSpeed) :
		m_frequency(frequency),
		m_radius(radius),
		m_animationSpeed(animationSpeed)
	{

	}
}