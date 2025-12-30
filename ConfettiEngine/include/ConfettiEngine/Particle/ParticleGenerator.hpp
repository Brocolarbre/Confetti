#pragma once

#include "ParticleData.hpp"
#include "ParticleBoundaries.hpp"
#include "ConfettiEngine/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class ParticleGenerator
	{
	public:
		static ParticleData generateParticle(RandomNumberGenerator& generator, const ParticleBoundaries& boundaries, float elapsedTime);
	};
}