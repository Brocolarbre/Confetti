#pragma once

#include "Particle.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
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

	class ParticleGenerator
	{
	public:
		static Particle generate(RandomNumberGenerator& generator, const ParticleBoundaries& boundaries, float elapsedTime, unsigned int emitterType, unsigned int emitterInstance);
	};
}