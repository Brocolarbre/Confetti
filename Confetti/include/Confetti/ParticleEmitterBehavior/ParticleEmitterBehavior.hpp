#pragma once

#include <memory>

namespace cft
{
	class ParticleEmitterBehavior
	{
	public:
		virtual std::unique_ptr<ParticleEmitterBehavior> clone() const = 0;
	};
}