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

	void GrowInParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		float end = m_duration.normalize(particle.lifetime);

		if (progress > end)
			return;

		float t = glm::min(progress / end, 1.0f);
		particle.scale = t * particle.initialScale;
	}
}