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

	void FadeInParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		float end = m_duration.normalize(particle.lifetime);

		if (progress > end)
			return;

		float t = glm::min(progress / end, 1.0f);
		particle.color.a = t * particle.initialColor.a;
	}
}