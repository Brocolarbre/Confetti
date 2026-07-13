#include "Confetti/ParticleBehavior/FadeInParticleBehavior.hpp"

namespace cft
{
	FadeInParticleBehavior::FadeInParticleBehavior(ParticleTime duration) :
		m_duration(duration)
	{

	}

	void FadeInParticleBehavior::evaluate(float elapsedTime, float normalizedAge, ParticleView& particle)
	{
		float end = m_duration.normalize(particle.lifetime);

		if (normalizedAge > end)
			return;

		float t = glm::min(normalizedAge / end, 1.0f);
		particle.color.a = t * particle.initialColor.a;
	}
}