#include "Confetti/ParticleBehavior/FlickerParticleBehavior.hpp"

namespace cft
{
	FlickerParticleBehavior::FlickerParticleBehavior(float minimumBrightness, float maximumBrightness, float speed) :
		m_minimumBrightness(minimumBrightness),
		m_maximumBrightness(maximumBrightness),
		m_speed(speed)
	{

	}

	std::unique_ptr<ParticleBehavior> FlickerParticleBehavior::clone() const
	{
		return std::make_unique<FlickerParticleBehavior>(*this);
	}

	void FlickerParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		float t = glm::sin(elapsedTime * m_speed + particle.phase) * 0.5f + 0.5f;
		particle.color = (1.0f - t) * particle.initialColor * glm::vec4(glm::vec3(m_minimumBrightness), 1.0f) + t * particle.initialColor * glm::vec4(glm::vec3(m_maximumBrightness), 1.0f);
	}
}