#pragma once

#include <glm/glm.hpp>

namespace cft
{
	struct PathPoint
	{
		glm::vec4 color;
		glm::vec3 position;
		float thickness;
		float distanceOnTrail;
		float spawnTime;
	};
}