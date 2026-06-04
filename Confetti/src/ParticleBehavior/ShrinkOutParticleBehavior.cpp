#include "Confetti/ParticleBehavior/ShrinkOutParticleBehavior.hpp"

namespace cft
{
	ShrinkOutParticleBehavior::ShrinkOutParticleBehavior(float start) :
		m_start(start)
	{

	}

	std::unique_ptr<ParticleBehavior> ShrinkOutParticleBehavior::clone() const
	{
		return std::make_unique<ShrinkOutParticleBehavior>(*this);
	}

	void ShrinkOutParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		if (progress < m_start)
			return;

		float t = glm::max(progress - m_start, 0.0f) / (1.0f - m_start);
		particle.scale = (1.0f - t) * particle.initialScale;
	}
}