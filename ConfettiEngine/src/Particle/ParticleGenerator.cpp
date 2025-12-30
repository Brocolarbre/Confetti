#include "ConfettiEngine/Particle/ParticleGenerator.hpp"

namespace cft
{
	ParticleData ParticleGenerator::generateParticle(RandomNumberGenerator& generator, const ParticleBoundaries& boundaries, float elapsedTime)
	{
		return ParticleData{
			generator.generate(boundaries.minimumColor, boundaries.maximumColor),
			generator.generate(boundaries.minimumPosition, boundaries.maximumPosition),
			generator.generate(boundaries.minimumVelocity, boundaries.maximumVelocity),
			generator.generate(boundaries.minimumScale, boundaries.maximumScale),
			generator.generate(boundaries.minimumLifetime, boundaries.maximumLifetime),
			elapsedTime
		};
	}
}