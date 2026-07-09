#pragma once

#include "RenderDescriptor.hpp"
#include "SpawnTrigger.hpp"
#include "TrailConfiguration.hpp"

namespace cft
{
	struct ParticleEmitter
	{
		unsigned int poolId;
		unsigned int particleSpawnerId;
		unsigned int emissionPatternId;
		std::optional<TrailConfiguration> trailConfiguration;
		std::optional<SpawnTrigger> spawnTrigger;
		RenderDescriptor renderDescriptor;
		std::vector<unsigned int> forceFieldIds;
		std::vector<unsigned int> motionBehaviorIds;
		std::vector<unsigned int> particleBehaviorIds;
	};
}