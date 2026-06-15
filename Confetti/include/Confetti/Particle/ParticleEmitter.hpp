#pragma once

#include <glm/glm.hpp>
#include <optional>
#include <vector>

namespace cft
{
	struct ParticleEmitter
	{
		unsigned int pool;
		unsigned int particleSpawner;
		unsigned int spawnPolicy;
		std::optional<unsigned int> spriteSheet;
		std::vector<unsigned int> forceFields;
		std::vector<unsigned int> motionBehaviors;
		std::vector<unsigned int> particleBehaviors;
	};
}