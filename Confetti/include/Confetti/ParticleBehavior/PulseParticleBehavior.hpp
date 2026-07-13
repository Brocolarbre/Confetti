#pragma once

#include "ParticleBehavior.hpp"

namespace cft
{
	class PulseParticleBehavior : public Cloneable<PulseParticleBehavior, ParticleBehavior>
	{
	private:
		glm::vec4 m_colorA;
		glm::vec4 m_colorB;
		float m_speed;

	public:
		PulseParticleBehavior(const glm::vec4& colorA, const glm::vec4& colorB, float speed);

		void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) override;
	};
}