#pragma once

#include "Trail.hpp"

namespace cft
{
	struct Ribbon
	{
		unsigned int ribbonRegistryId;
		unsigned int fromParticleId;
		unsigned int toParticleId;
		float spawnTime;
		std::deque<TrailPoint> points;
	};

	struct RibbonView
	{
		const unsigned int& ribbonRegistryId;
		const unsigned int& fromParticleId;
		const unsigned int& toParticleId;
		const float& spawnTime;
		std::deque<TrailPoint>& points;
	};
}