#pragma once

#include "ParticleBehavior.hpp"

namespace cft
{
	class GrowInParticleBehavior : public ParticleBehavior
	{
	private:
		float m_end;

	public:
		GrowInParticleBehavior(float end);

		std::unique_ptr<ParticleBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, float progress, ParticleView& particle) override;
	};
}