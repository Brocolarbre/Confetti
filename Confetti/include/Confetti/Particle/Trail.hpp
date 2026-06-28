#pragma once

#include <glm/glm.hpp>
#include <deque>

namespace cft
{
	struct TrailPoint
	{
		glm::vec4 color;
		glm::vec3 position;
		float thickness;
		float spawnTime;
	};

	struct Trail
	{
		unsigned int trailRegistryId;
		unsigned int particleId;
		float particleDeathTime;
		std::deque<TrailPoint> points;
	};
}