#pragma once

#include "ParticleBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class FadeOutParticleBehavior : public CloneableParticleBehavior<FadeOutParticleBehavior>
	{
	private:
		ParticleTime m_duration;

	public:
		FadeOutParticleBehavior(ParticleTime duration);

		void evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle) override;
	};
}