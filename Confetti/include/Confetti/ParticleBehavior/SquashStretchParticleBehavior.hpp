#pragma once

#include "ParticleBehavior.hpp"

namespace cft
{
	class SquashStretchParticleBehavior : public Cloneable<SquashStretchParticleBehavior, ParticleBehavior>
	{
	private:
		glm::vec2 m_strength;
		float m_speed;

	public:
		SquashStretchParticleBehavior(const glm::vec2& strength, float speed);

		void evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle) override;
	};
}