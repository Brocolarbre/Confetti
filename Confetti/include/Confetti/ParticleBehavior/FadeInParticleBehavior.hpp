#pragma once

#include "ParticleBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class FadeInParticleBehavior : public Cloneable<FadeInParticleBehavior, ParticleBehavior>
	{
	private:
		ParticleTime m_duration;

	public:
		FadeInParticleBehavior(ParticleTime duration);

		void evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle) override;
	};
}