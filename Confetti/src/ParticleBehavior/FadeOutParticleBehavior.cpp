#include "Confetti/ParticleBehavior/FadeOutParticleBehavior.hpp"

namespace cft
{
	FadeOutParticleBehavior::FadeOutParticleBehavior(ParticleTime duration) :
		m_duration(duration)
	{

	}

	std::unique_ptr<ParticleBehavior> FadeOutParticleBehavior::clone() const
	{
		return std::make_unique<FadeOutParticleBehavior>(*this);
	}

	void FadeOutParticleBehavior::evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle)
	{
		float duration = m_duration.normalize(particle.lifetime);
		float start = 1.0f - duration;

		if (particleNormalizedAge < start)
			return;

		float t = (particleNormalizedAge - start) / duration;
		particle.color.a = (1.0f - t) * particle.initialColor.a;
	}
}