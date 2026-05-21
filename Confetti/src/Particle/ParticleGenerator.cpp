#include "ConfettiEngine/Particle/ParticleGenerator.hpp"

namespace cft
{
	Particle ParticleGenerator::generate(RandomNumberGenerator& generator, const ParticleBoundaries& boundaries, float elapsedTime, unsigned int emitterType, unsigned int emitterInstance)
	{
		return Particle{
			generator.generate(boundaries.minimumColor, boundaries.maximumColor),
			generator.generate(boundaries.minimumPosition, boundaries.maximumPosition),
			generator.generate(boundaries.minimumVelocity, boundaries.maximumVelocity),
			generator.generate(boundaries.minimumScale, boundaries.maximumScale),
			generator.generate(boundaries.minimumLifetime, boundaries.maximumLifetime),
			elapsedTime,
			emitterType,
			emitterInstance
		};
	}
}