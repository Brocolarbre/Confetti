#include "Confetti/ParticleSpawner/RandomParticleSpawner.hpp"

namespace cft
{
	Particle RandomParticleSpawner::generateParticle(RandomNumberGenerator& generator, const ParticleBoundaries& boundaries, float elapsedTime, unsigned int id)
	{
		return Particle{
			generator.generate(boundaries.minimumColor, boundaries.maximumColor),
			generator.generate(boundaries.minimumPosition, boundaries.maximumPosition),
			generator.generate(boundaries.minimumVelocity, boundaries.maximumVelocity),
			generator.generate(boundaries.minimumScale, boundaries.maximumScale),
			generator.generate(boundaries.minimumLifetime, boundaries.maximumLifetime),
			elapsedTime,
			id
		};
	}

	RandomParticleSpawner::RandomParticleSpawner(RandomNumberGenerator& randomNumberGenerator, const ParticleBoundaries& boundaries) :
		m_randomNumberGenerator(randomNumberGenerator),
		m_boundaries(boundaries)
	{

	}

	std::unique_ptr<ParticleSpawner> RandomParticleSpawner::clone() const
	{
		return std::make_unique<RandomParticleSpawner>(*this);
	}

	float RandomParticleSpawner::getMaxiumParticleLifetime() const
	{
		return m_boundaries.maximumLifetime;
	}

	std::vector<Particle> RandomParticleSpawner::spawn(unsigned int count, float elapsedTime, float deltaTime, unsigned int id)
	{
		std::vector<Particle> particles;
		particles.reserve(count);

		for (unsigned int i = 0; i < count; ++i)
			particles.push_back(generateParticle(m_randomNumberGenerator, m_boundaries, elapsedTime, id));

		return particles;

		// m_forceFieldSet.addForceFieldReferenceCount(particleEmitterInstance.forceFieldSetId, roundedSpawnCount);
	}
}