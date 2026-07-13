#pragma once

#include "ParticleBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class FadeOutParticleBehavior : public Cloneable<FadeOutParticleBehavior, ParticleBehavior>
	{
	private:
		ParticleTime m_duration;

	public:
		FadeOutParticleBehavior(ParticleTime duration);

		void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) override;
	};
}