#pragma once

#include <glm/glm.hpp>

namespace cft
{
	struct TimeRange
	{
		float spawnTime;
		float duration;
	};

	struct ParticleEmitterDescriptor
	{
		TimeRange timeRange;
		unsigned int emitterBehavior;
		unsigned int emitter;
		glm::vec3 position;
		glm::vec3 velocity;
	};

	struct ParticleEffect
	{
		std::vector<ParticleEmitterDescriptor> emitters;
	};
}