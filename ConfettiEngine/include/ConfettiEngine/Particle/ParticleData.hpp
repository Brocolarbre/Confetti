#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace cft
{
	struct ParticleData
	{
		std::vector<glm::vec4> color;
		std::vector<glm::vec3> position;
		std::vector<glm::vec3> velocity;
		std::vector<glm::vec2> scale;
		std::vector<float> lifetime;
		std::vector<float> spawnTime;

		unsigned int size = 0;
	};
}