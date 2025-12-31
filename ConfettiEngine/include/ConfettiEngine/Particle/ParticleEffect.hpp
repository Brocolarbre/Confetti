#pragma once

#include <vector>

namespace cft
{
	struct ParticleEffect
	{
		float spawnTime;
		float lifetime;
		std::vector<unsigned int> emitters;
	};
}