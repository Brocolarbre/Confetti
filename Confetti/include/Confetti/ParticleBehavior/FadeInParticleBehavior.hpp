#pragma once

#include "ParticleBehavior.hpp"

namespace cft
{
	class FadeInParticleBehavior : public ParticleBehavior
	{
	private:
		float m_end;

	public:
		FadeInParticleBehavior(float end);

		std::unique_ptr<ParticleBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, float progress, ParticleView& particle) override;
	};
}