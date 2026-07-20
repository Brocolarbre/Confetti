#pragma once

#include "Confetti/Data/ParticleEffectDescriptor.hpp"

namespace cft
{
	struct ParticleEffectInstance
	{
		float spawnTime;
		std::vector<ParticleEmitterSpawnContext> emitterSpawnContexts;
	};
}