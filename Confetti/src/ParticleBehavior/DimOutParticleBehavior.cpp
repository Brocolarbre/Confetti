#include "Confetti/ParticleBehavior/DimOutParticleBehavior.hpp"

namespace cft
{
	DimOutParticleBehavior::DimOutParticleBehavior(float start) :
		m_start(start)
	{

	}

	std::unique_ptr<ParticleBehavior> DimOutParticleBehavior::clone() const
	{
		return std::make_unique<DimOutParticleBehavior>(*this);
	}

	void DimOutParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		if (progress < m_start)
			return;

		float t = glm::max(progress - m_start, 0.0f) / (1.0f - m_start);
		float alpha = particle.color.a;
		particle.color = (1.0f - t) * particle.initialColor;
		particle.color.a = alpha;
	}
}