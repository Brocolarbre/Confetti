#pragma once

#include "ParticleBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class FadeOutParticleBehavior : public ParticleBehavior
	{
	private:
		ParticleTime m_duration;

	public:
		FadeOutParticleBehavior(ParticleTime duration);

		std::unique_ptr<ParticleBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, float progress, ParticleView& particle) override;
	};
}