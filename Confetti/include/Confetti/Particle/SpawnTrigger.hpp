#pragma once

#include "ParticleEffect.hpp"

#include <optional>

namespace cft
{
	struct PeriodicSpawnTrigger
	{
		ParticleEmitterDescriptor emitterDescriptor;
		float interval;
	};

	struct SpawnTrigger
	{
		unsigned int maximumRecursionDepth;
		std::optional<ParticleEmitterDescriptor> spawnEmitterDescriptor;
		std::optional<ParticleEmitterDescriptor> deathEmitterDescriptor;
		std::optional<PeriodicSpawnTrigger> periodicEmitterDescriptor;
	};
}