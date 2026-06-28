#pragma once

#include "RenderDescriptor.hpp"
#include "SpawnTrigger.hpp"
#include "TrailConfiguration.hpp"

namespace cft
{
	struct ParticleEmitter
	{
		unsigned int pool;
		unsigned int particleSpawner;
		unsigned int spawnPolicy;
		std::optional<TrailConfiguration> trailConfiguration;
		std::optional<SpawnTrigger> spawnTrigger;
		RenderDescriptor renderDescriptor;
		std::vector<unsigned int> forceFields;
		std::vector<unsigned int> motionBehaviors;
		std::vector<unsigned int> particleBehaviors;
	};
}