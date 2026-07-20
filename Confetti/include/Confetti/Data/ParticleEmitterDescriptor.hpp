#pragma once

#include "RenderConfiguration.hpp"
#include "RibbonConfiguration.hpp"
#include "SpawnTriggerDescriptor.hpp"
#include "TrailConfiguration.hpp"

namespace cft
{
	struct ParticleEmitterDescriptor
	{
		unsigned int poolId;
		unsigned int particleSpawnerId;
		unsigned int emissionPatternId;
		std::optional<TrailConfiguration> trailConfiguration;
		std::optional<RibbonConfiguration> ribbonConfiguration;
		std::optional<SpawnTriggerDescriptor> spawnTriggerDescriptor;
		RenderConfiguration renderConfiguration;
		std::vector<unsigned int> forceFieldIds;
		std::vector<unsigned int> motionBehaviorIds;
		std::vector<unsigned int> visualBehaviorIds;
	};
}