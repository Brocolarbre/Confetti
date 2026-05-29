#pragma once

#include "ParticleEmitterBehavior.hpp"

namespace cft
{
	class RandomParticleEmitterBehavior : public ParticleEmitterBehavior
	{
	public:
		std::unique_ptr<ParticleEmitterBehavior> clone() const override;
	};
}