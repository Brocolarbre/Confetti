#pragma once

#include "Particle.hpp"
#include "ParticleBoundaries.hpp"
#include "ConfettiEngine/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class ParticleGenerator
	{
	public:
		static Particle generateParticle(RandomNumberGenerator& generator, const ParticleBoundaries& boundaries, float elapsedTime);
	};
}