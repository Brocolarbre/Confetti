#pragma once

#include <glm/glm.hpp>

namespace cft
{
	struct ParticleData
	{
		glm::vec4 color;
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec2 scale;
		float lifetime;
		float spawnTime;
	};
}