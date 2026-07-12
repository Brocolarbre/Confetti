#pragma once

#include "ParticleBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class ShrinkOutParticleBehavior : public CloneableParticleBehavior<ShrinkOutParticleBehavior>
	{
	private:
		ParticleTime m_duration;

	public:
		ShrinkOutParticleBehavior(ParticleTime duration);

		void evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle) override;
	};
}