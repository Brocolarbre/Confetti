#include "Confetti/ParticleBehavior/FadeOutParticleBehavior.hpp"

namespace cft
{
	FadeOutParticleBehavior::FadeOutParticleBehavior(float start) :
		m_start(start)
	{

	}

	std::unique_ptr<ParticleBehavior> FadeOutParticleBehavior::clone() const
	{
		return std::make_unique<FadeOutParticleBehavior>(*this);
	}

	void FadeOutParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		float t = (progress - m_start) / (1.0f - m_start);
		particle.color.a = (1.0f - t) * particle.initialColor.a + t * glm::vec3(0.0f);
	}
}