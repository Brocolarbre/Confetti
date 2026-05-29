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
		glm::vec3 position;
		TimeRange timeRange;
		unsigned int emitterBehavior;
		unsigned int emitter;
	};

	struct ParticleEffect
	{
		std::vector<ParticleEmitterDescriptor> emitters;
	};
}