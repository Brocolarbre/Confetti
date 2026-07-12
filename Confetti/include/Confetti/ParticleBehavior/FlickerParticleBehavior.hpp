#pragma once

#include "ParticleBehavior.hpp"

namespace cft
{
	class FlickerParticleBehavior : public Cloneable<FlickerParticleBehavior, ParticleBehavior>
	{
	private:
		float m_minimumBrightness;
		float m_maximumBrightness;
		float m_speed;

	public:
		FlickerParticleBehavior(float minimumBrightness, float maximumBrightness, float speed);

		void evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle) override;
	};
}