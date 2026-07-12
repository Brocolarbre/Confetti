#pragma once

#include "ParticleBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class GrowInParticleBehavior : public Cloneable<GrowInParticleBehavior, ParticleBehavior>
	{
	private:
		ParticleTime m_duration;

	public:
		GrowInParticleBehavior(ParticleTime duration);

		void evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle) override;
	};
}