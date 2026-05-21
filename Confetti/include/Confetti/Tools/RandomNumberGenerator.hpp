#pragma once

#include <glm/glm.hpp>
#include <random>

namespace cft
{
	class RandomNumberGenerator
	{
	private:
		std::default_random_engine m_engine;
		std::uniform_real_distribution<float> m_distribution;

	public:
		RandomNumberGenerator(unsigned int seed = 0);

		float generate(float min, float max);
		glm::vec2 generate(const glm::vec2& min, const glm::vec2& max);
		glm::vec3 generate(const glm::vec3& min, const glm::vec3& max);
		glm::vec4 generate(const glm::vec4& min, const glm::vec4& max);
	};
}