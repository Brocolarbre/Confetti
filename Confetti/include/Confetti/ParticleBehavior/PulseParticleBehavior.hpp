#pragma once

#include "ParticleBehavior.hpp"

namespace cft
{
	class PulseParticleBehavior : public ParticleBehavior
	{
	private:
		glm::vec4 m_colorA;
		glm::vec4 m_colorB;
		float m_speed;

	public:
		PulseParticleBehavior(const glm::vec4& colorA, const glm::vec4& colorB, float speed);

		std::unique_ptr<ParticleBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, float progress, ParticleView& particle) override;
	};
}