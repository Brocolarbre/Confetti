#pragma once

#include "ParticleData.hpp"

#include <vector>

namespace cft
{
	struct ParticlePool
	{
		std::vector<glm::vec4> color;
		std::vector<glm::vec3> position;
		std::vector<glm::vec3> velocity;
		std::vector<glm::vec2> scale;
		std::vector<float> lifetime;
		std::vector<float> spawnTime;

		unsigned int capacity;
		unsigned int count;

		ParticlePool();

		void allocate(unsigned int capacity);
		void add(const ParticleData& data);
		void remove(unsigned int index);
	};
}