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

	void PulseParticleBehavior::evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle)
	{
		float t = glm::sin(elapsedTime * m_speed + particle.phase) * 0.5f + 0.5f;
		particle.color = glm::mix(m_colorA, m_colorB, t);
	}
}