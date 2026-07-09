#include "Confetti/ParticleBehavior/DimOutParticleBehavior.hpp"

namespace cft
{
	DimOutParticleBehavior::DimOutParticleBehavior(ParticleTime duration) :
		m_duration(duration)
	{

	}

	std::unique_ptr<ParticleBehavior> DimOutParticleBehavior::clone() const
	{
		return std::make_unique<DimOutParticleBehavior>(*this);
	}

	void DimOutParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		float duration = m_duration.normalize(particle.lifetime);
		float start = 1.0f - duration;

		if (progress < start)
			return;

		float t = (progress - start) / duration;
		float alpha = particle.color.a;
		particle.color = (1.0f - t) * particle.initialColor;
		particle.color.a = alpha;
	}
}