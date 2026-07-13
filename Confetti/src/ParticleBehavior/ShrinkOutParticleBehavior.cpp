#include "Confetti/ParticleBehavior/ShrinkOutParticleBehavior.hpp"

namespace cft
{
	ShrinkOutParticleBehavior::ShrinkOutParticleBehavior(ParticleTime duration) :
		m_duration(duration)
	{

	}

	void ShrinkOutParticleBehavior::evaluate(float elapsedTime, float normalizedAge, ParticleView& particle)
	{
		float duration = m_duration.normalize(particle.lifetime);
		float start = 1.0f - duration;

		if (normalizedAge < start)
			return;

		float t = (normalizedAge - start) / duration;
		particle.scale = (1.0f - t) * particle.initialScale;
	}
}