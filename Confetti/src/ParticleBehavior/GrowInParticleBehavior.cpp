#include "Confetti/ParticleBehavior/GrowInParticleBehavior.hpp"

namespace cft
{
	GrowInParticleBehavior::GrowInParticleBehavior(ParticleTime duration) :
		m_duration(duration)
	{

	}

	std::unique_ptr<ParticleBehavior> GrowInParticleBehavior::clone() const
	{
		return std::make_unique<GrowInParticleBehavior>(*this);
	}

	void GrowInParticleBehavior::evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle)
	{
		float end = m_duration.normalize(particle.lifetime);

		if (particleNormalizedAge > end)
			return;

		float t = glm::min(particleNormalizedAge / end, 1.0f);
		particle.scale = t * particle.initialScale;
	}
}