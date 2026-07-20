#pragma once

#include "ParticleEffectDescriptor.hpp"

#include <optional>

namespace cft
{
	struct PeriodicSpawnTriggerContext
	{
		ParticleEmitterSpawnContext emitterSpawnContext;
		float interval;
	};

	struct SpawnTriggerDescriptor
	{
		unsigned int maximumRecursionDepth;
		std::optional<ParticleEmitterSpawnContext> spawnEmitterSpawnContext;
		std::optional<ParticleEmitterSpawnContext> deathEmitterSpawnContext;
		std::optional<PeriodicSpawnTriggerContext> periodicEmitterSpawnContext;
	};
}