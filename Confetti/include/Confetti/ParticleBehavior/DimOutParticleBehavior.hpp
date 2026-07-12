#pragma once

#include "ParticleBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class DimOutParticleBehavior : public CloneableParticleBehavior<DimOutParticleBehavior>
	{
	private:
		ParticleTime m_duration;

	public:
		DimOutParticleBehavior(ParticleTime duration);

		void evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle) override;
	};
}