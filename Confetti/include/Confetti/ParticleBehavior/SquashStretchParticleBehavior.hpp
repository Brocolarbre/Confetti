#pragma once

#include "ParticleBehavior.hpp"

namespace cft
{
	class SquashStretchParticleBehavior : public ParticleBehavior
	{
	private:
		glm::vec2 m_strength;
		float m_speed;

	public:
		SquashStretchParticleBehavior(const glm::vec2& strength, float speed);

		std::unique_ptr<ParticleBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, float progress, ParticleView& particle) override;
	};
}