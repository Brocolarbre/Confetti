#pragma once

#include "ParticleBehavior.hpp"

namespace cft
{
	class DimOutParticleBehavior : public ParticleBehavior
	{
	private:
		float m_start;

	public:
		DimOutParticleBehavior(float start);

		std::unique_ptr<ParticleBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, float progress, ParticleView& particle) override;
	};
}