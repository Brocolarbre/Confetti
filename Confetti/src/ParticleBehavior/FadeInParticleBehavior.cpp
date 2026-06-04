#include "Confetti/ParticleBehavior/FadeInParticleBehavior.hpp"

namespace cft
{
	FadeInParticleBehavior::FadeInParticleBehavior(float end) :
		m_end(end)
	{

	}

	std::unique_ptr<ParticleBehavior> FadeInParticleBehavior::clone() const
	{
		return std::make_unique<FadeInParticleBehavior>(*this);
	}

	void FadeInParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		if (progress > m_end)
			return;

		float t = glm::min(progress / m_end, 1.0f);
		particle.color.a = t * particle.initialColor.a;
	}
}