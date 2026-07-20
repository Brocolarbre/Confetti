#pragma once

#include "TimeRange.hpp"
#include "MotionState.hpp"

namespace cft
{
	struct ParticleEmitterSpawnContext
	{
		unsigned int emitterDescriptorId;
		TimeRange timeRange;
		MotionState initialMotionState;
		std::vector<unsigned int> forceFieldIds;
		std::vector<unsigned int> motionBehaviorIds;
	};

	struct ParticleEffectDescriptor
	{
		std::vector<ParticleEmitterSpawnContext> emitterSpawnContexts;
	};
}