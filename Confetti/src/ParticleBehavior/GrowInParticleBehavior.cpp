#include "Confetti/ParticleBehavior/GrowInParticleBehavior.hpp"

namespace cft
{
	GrowInParticleBehavior::GrowInParticleBehavior(float end) :
		m_end(end)
	{

	}

	std::unique_ptr<ParticleBehavior> GrowInParticleBehavior::clone() const
	{
		return std::make_unique<GrowInParticleBehavior>(*this);
	}

	void GrowInParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		if (progress > m_end)
			return;

		float t = glm::min(progress / m_end, 1.0f);
		particle.scale = t * particle.initialScale;
	}
}