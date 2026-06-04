#include "Confetti/ParticleBehavior/FlickerParticleBehavior.hpp"

namespace cft
{
	FlickerParticleBehavior::FlickerParticleBehavior(const glm::vec4& colorA, const glm::vec4& colorB, float speed) :
		m_colorA(colorA),
		m_colorB(colorB),
		m_speed(speed)
	{

	}

	std::unique_ptr<ParticleBehavior> FlickerParticleBehavior::clone() const
	{
		return std::make_unique<FlickerParticleBehavior>(*this);
	}

	void FlickerParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		float t = glm::cos(elapsedTime * m_speed + static_cast<float>(particle.id)) * 0.5f + 0.5f;
		particle.color = (1.0f - t) * m_colorA + t * m_colorB;
	}
}