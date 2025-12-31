#pragma once

#include "ParticlePool.hpp"

namespace cft
{
	struct ParticleEmitter
	{
		unsigned int type;
		float spawnTime;
		float lifetime;
		float spawnRate;
		float accumulator;
		ParticleBoundaries boundaries;
	};
}