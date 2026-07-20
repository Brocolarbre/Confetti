#pragma once

#include "PathPoint.hpp"

#include <deque>

namespace cft
{
	struct Trail
	{
		unsigned int trailRegistryId;
		unsigned int particleId;
		float particleDeathTime;
		glm::vec4 particleColor;
		std::deque<PathPoint> points;
	};
}