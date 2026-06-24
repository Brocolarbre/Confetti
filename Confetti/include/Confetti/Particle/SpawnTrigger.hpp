#pragma once

#include "ParticleEffect.hpp"

#include <optional>

namespace cft
{
	struct PeriodicSpawnTrigger
	{
		ParticleEmitterDescriptor emitter;
		float interval;
	};

	struct SpawnTrigger
	{
		unsigned int maximumRecursionDepth;
		std::optional<ParticleEmitterDescriptor> spawnEmitter;
		std::optional<ParticleEmitterDescriptor> deathEmitter;
		std::optional<PeriodicSpawnTrigger> periodicEmitter;
	};
}