#include "Confetti/ParticleBehavior/GrowInParticleBehavior.hpp"

namespace cft
{
	GrowInParticleBehavior::GrowInParticleBehavior(ParticleTime duration) :
		m_duration(duration)
	{

	}

	void GrowInParticleBehavior::evaluate(float elapsedTime, float normalizedAge, ParticleView& particle)
	{
		float end = m_duration.normalize(particle.lifetime);

		if (normalizedAge > end)
			return;

		float t = glm::min(normalizedAge / end, 1.0f);
		particle.scale = t * particle.initialScale;
	}
}