#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace cft
{
	struct ParticleEmitter
	{
	public:
		unsigned int pool;
		unsigned int particleSpawner;
		unsigned int spawnPolicy;
		std::vector<unsigned int> forceFields;
		std::vector<unsigned int> motionBehaviors;
		std::vector<unsigned int> particleBehaviors;
	};
}