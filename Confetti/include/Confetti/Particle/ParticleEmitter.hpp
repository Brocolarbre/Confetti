#pragma once

#include <vector>

namespace cft
{
	struct ParticleEmitter
	{
	public:
		std::vector<unsigned int> forceFields;
		unsigned int particleBehavior;
		unsigned int particleSpawner;
		unsigned int spawnPolicy;
		unsigned int pool;
	};
}