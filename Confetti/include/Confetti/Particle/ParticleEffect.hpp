#pragma once

#include "TimeRange.hpp"
#include "Transform.hpp"

namespace cft
{
	struct ParticleEmitterDescriptor
	{
		unsigned int emitterId;
		TimeRange timeRange;
		Transform transform;
		std::vector<unsigned int> forceFields;
		std::vector<unsigned int> motionBehaviors;
	};

	struct ParticleEffect
	{
		std::vector<ParticleEmitterDescriptor> emitters;
	};
}