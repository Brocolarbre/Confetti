#pragma once

#include "PathPoint.hpp"

#include <deque>

namespace cft
{
	struct Ribbon
	{
		unsigned int ribbonRegistryId;
		unsigned int fromParticleId;
		unsigned int toParticleId;
		float spawnTime;
		std::deque<PathPoint> points;
	};

	struct RibbonView
	{
		const unsigned int& ribbonRegistryId;
		const unsigned int& fromParticleId;
		const unsigned int& toParticleId;
		const float& spawnTime;
		std::deque<PathPoint>& points;
	};
}