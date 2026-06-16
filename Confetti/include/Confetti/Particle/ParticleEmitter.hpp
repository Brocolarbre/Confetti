#pragma once

#include "RenderDescriptor.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace cft
{
	struct ParticleEmitter
	{
		unsigned int pool;
		unsigned int particleSpawner;
		unsigned int spawnPolicy;
		RenderDescriptor renderDescriptor;
		std::vector<unsigned int> forceFields;
		std::vector<unsigned int> motionBehaviors;
		std::vector<unsigned int> particleBehaviors;
	};
}