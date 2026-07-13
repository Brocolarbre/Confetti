#include "Confetti/ParticleBehavior/FlickerParticleBehavior.hpp"

namespace cft
{
	FlickerParticleBehavior::FlickerParticleBehavior(float minimumBrightness, float maximumBrightness, float speed) :
		m_minimumBrightness(minimumBrightness),
		m_maximumBrightness(maximumBrightness),
		m_speed(speed)
	{

	}

	void FlickerParticleBehavior::evaluate(float elapsedTime, float normalizedAge, ParticleView& particle)
	{
		float t = glm::sin(elapsedTime * m_speed + particle.phase) * 0.5f + 0.5f;

		glm::vec4 colorA = particle.initialColor * glm::vec4(glm::vec3(m_minimumBrightness), 1.0f);
		glm::vec4 colorB = particle.initialColor * glm::vec4(glm::vec3(m_maximumBrightness), 1.0f);
		particle.color = glm::mix(colorA, colorB, t);
	}
}