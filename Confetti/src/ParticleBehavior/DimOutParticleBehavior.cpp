#include "Confetti/ParticleBehavior/DimOutParticleBehavior.hpp"

namespace cft
{
	DimOutParticleBehavior::DimOutParticleBehavior(ParticleTime duration) :
		m_duration(duration)
	{

	}

	void DimOutParticleBehavior::evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle)
	{
		float duration = m_duration.normalize(particle.lifetime);
		float start = 1.0f - duration;

		if (particleNormalizedAge < start)
			return;

		float t = (particleNormalizedAge - start) / duration;
		float alpha = particle.color.a;
		particle.color = (1.0f - t) * particle.initialColor;
		particle.color.a = alpha;
	}
}