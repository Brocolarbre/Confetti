#pragma once

#include "ParticleBehavior.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class RandomParticleBehavior : public ParticleBehavior
	{
	private:
		RandomNumberGenerator& m_randomNumberGenerator;

	public:
		RandomParticleBehavior(RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<ParticleBehavior> clone() const override;
		void update(float elapsedTime, float deltaTime, ParticleView& particle) override;
	};
}