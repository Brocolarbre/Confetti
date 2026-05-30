#pragma once

#include "Confetti/Particle/ParticleEmitter.hpp"

#include <memory>

namespace cft
{
	class ParticleEmitterBehavior
	{
	public:
		virtual std::unique_ptr<ParticleEmitterBehavior> clone() const = 0;
		virtual void update(float elapsedTime, float deltaTime, ParticleEmitterView& particleEmitter) = 0;
	};
}