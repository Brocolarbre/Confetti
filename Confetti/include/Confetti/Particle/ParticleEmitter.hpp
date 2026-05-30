#pragma once

#include <glm/glm.hpp>
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

	struct ParticleEmitterView
	{
		glm::vec3& position;
		glm::vec3& velocity;
	};
}