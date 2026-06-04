#pragma once

#include "ParticleBehavior.hpp"

namespace cft
{
	class ShrinkOutParticleBehavior : public ParticleBehavior
	{
	private:
		float m_start;

	public:
		ShrinkOutParticleBehavior(float start);

		std::unique_ptr<ParticleBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, float progress, ParticleView& particle) override;
	};
}