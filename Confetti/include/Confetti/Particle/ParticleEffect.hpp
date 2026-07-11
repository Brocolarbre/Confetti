#pragma once

#include "TimeRange.hpp"
#include "MotionState.hpp"

namespace cft
{
	struct ParticleEmitterDescriptor
	{
		unsigned int emitterId;
		TimeRange timeRange;
		MotionState motionState;
		std::vector<unsigned int> forceFieldIds;
		std::vector<unsigned int> motionBehaviorIds;
	};

	struct ParticleEffect
	{
		std::vector<ParticleEmitterDescriptor> emitterDescriptors;
	};
}