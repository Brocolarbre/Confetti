#include "Confetti/ParticleBehavior/ShrinkOutParticleBehavior.hpp"

namespace cft
{
	ShrinkOutParticleBehavior::ShrinkOutParticleBehavior(ParticleTime duration) :
		m_duration(duration)
	{

	}

	std::unique_ptr<ParticleBehavior> ShrinkOutParticleBehavior::clone() const
	{
		return std::make_unique<ShrinkOutParticleBehavior>(*this);
	}

	void ShrinkOutParticleBehavior::evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle)
	{
		float duration = m_duration.normalize(particle.lifetime);
		float start = 1.0f - duration;

		if (particleNormalizedAge < start)
			return;

		float t = (particleNormalizedAge - start) / duration;
		particle.scale = (1.0f - t) * particle.initialScale;
	}
}