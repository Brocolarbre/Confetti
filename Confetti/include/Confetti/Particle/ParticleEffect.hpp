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
		std::vector<unsigned int> forceFieldIds;
		std::vector<unsigned int> motionBehaviorIds;
	};

	struct ParticleEffect
	{
		std::vector<ParticleEmitterDescriptor> emitterDescriptors;
	};
}