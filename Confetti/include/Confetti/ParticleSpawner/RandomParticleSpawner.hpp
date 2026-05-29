#pragma once

#include "ParticleSpawner.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class RandomParticleSpawner : public ParticleSpawner
	{
	public:
		struct ParticleBoundaries
		{
			glm::vec4 minimumColor;
			glm::vec4 maximumColor;
			glm::vec3 minimumPosition;
			glm::vec3 maximumPosition;
			glm::vec3 minimumVelocity;
			glm::vec3 maximumVelocity;
			glm::vec2 minimumScale;
			glm::vec2 maximumScale;
			float minimumLifetime;
			float maximumLifetime;
		};

	private:
		ParticleBoundaries m_boundaries;
		RandomNumberGenerator& m_randomNumberGenerator;

		static Particle generateParticle(RandomNumberGenerator& generator, const ParticleBoundaries& boundaries, float elapsedTime, unsigned int id);

	public:
		RandomParticleSpawner(RandomNumberGenerator& randomNumberGenerator, const ParticleBoundaries& boundaries);

		std::unique_ptr<ParticleSpawner> clone() const override;
		float getMaxiumParticleLifetime() const override;
		std::vector<Particle> spawn(unsigned int count, float elapsedTime, float deltaTime, unsigned int id) override;
	};
}