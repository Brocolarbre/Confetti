#include "Confetti/ParticleBehavior/PulseParticleBehavior.hpp"

namespace cft
{
	PulseParticleBehavior::PulseParticleBehavior(const glm::vec4& colorA, const glm::vec4& colorB, float speed) :
		m_colorA(colorA),
		m_colorB(colorB),
		m_speed(speed)
	{

	}

	std::unique_ptr<ParticleBehavior> PulseParticleBehavior::clone() const
	{
		return std::make_unique<PulseParticleBehavior>(*this);
	}

	void PulseParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		float t = glm::sin(elapsedTime * m_speed + particle.phase) * 0.5f + 0.5f;
		particle.color = (1.0f - t) * m_colorA + t * m_colorB;
	}
}