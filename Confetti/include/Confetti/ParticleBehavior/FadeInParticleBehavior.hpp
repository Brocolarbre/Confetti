#pragma once

#include "ParticleBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class FadeInParticleBehavior : public ParticleBehavior
	{
	private:
		ParticleTime m_duration;

	public:
		FadeInParticleBehavior(ParticleTime duration);

		std::unique_ptr<ParticleBehavior> clone() const override;
		void evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle) override;
	};
}