#pragma once

#include "ParticleBoundaries.hpp"

namespace cft
{
	struct ParticleEmitter
	{
		float spawnRate;
		float accumulator;
		ParticleBoundaries boundaries;
	};
}