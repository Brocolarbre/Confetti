#pragma once

#include "ParticleBehavior.hpp"

namespace cft
{
	class FadeOutParticleBehavior : public ParticleBehavior
	{
	private:
		float m_start;

	public:
		FadeOutParticleBehavior(float start);

		std::unique_ptr<ParticleBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, float progress, ParticleView& particle) override;
	};
}