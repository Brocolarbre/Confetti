#include "Confetti/Simulation/Link/RibbonGenerator/WaveRibbonGenerator.hpp"

namespace cft
{
	glm::vec3 WaveRibbonGenerator::generateRibbonPoint(float t, float elapsedTime, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const
	{
		glm::vec3 a = fromParticle.postBehaviorPosition;
		glm::vec3 b = toParticle.postBehaviorPosition;

		glm::vec3 center = glm::mix(a, b, t);
		glm::vec3 axis = glm::normalize(b - a);

		glm::vec3 reference = glm::abs(axis.y) < 0.999f ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 normal = glm::normalize(glm::cross(axis, reference));

		float phase = elapsedTime * m_animationSpeed;
		float offset = glm::sin(t * m_frequency + phase) * m_amplitude;

		return center + normal * offset;
	}

	WaveRibbonGenerator::WaveRibbonGenerator(float frequency, float amplitude, float animationSpeed) :
		m_frequency(frequency),
		m_amplitude(amplitude),
		m_animationSpeed(animationSpeed)
	{

	}
}