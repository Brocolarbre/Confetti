#include "Confetti/ParticleBehavior/FadeInParticleBehavior.hpp"

namespace cft
{
	FadeInParticleBehavior::FadeInParticleBehavior(ParticleTime duration) :
		m_duration(duration)
	{

	}

	std::unique_ptr<ParticleBehavior> FadeInParticleBehavior::clone() const
	{
		return std::make_unique<FadeInParticleBehavior>(*this);
	}

	void FadeInParticleBehavior::evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle)
	{
		float end = m_duration.normalize(particle.lifetime);

		if (particleNormalizedAge > end)
			return;

		float t = glm::min(particleNormalizedAge / end, 1.0f);
		particle.color.a = t * particle.initialColor.a;
	}
}