#pragma once

#include "PathConfiguration.hpp"

namespace cft
{
	struct TrailConfiguration
	{
		float presistenceLifetime;
		float minimumSpawnDistance;
		std::optional<float> maximumSpawnTime;
		std::optional<unsigned int> maximumSegmentCount;
		PathConfiguration pathConfiguration;
	};
}