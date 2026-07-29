#pragma once

#include "Confetti/Export.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <random>

namespace cft
{
	class CONFETTI_API RandomNumberGenerator
	{
	private:
		std::mt19937_64 m_engine;
		std::uint64_t m_seed;

		std::uniform_int_distribution<int> m_integerDistribution;
		std::uniform_int_distribution<unsigned int> m_unsignedIntegerDistribution;
		std::uniform_real_distribution<float> m_realDistribution;

	public:
		RandomNumberGenerator(std::uint64_t seed = 0);

		std::uint64_t getSeed() const;
		void setSeed(std::uint64_t seed);
		void reset();

		int generate(int min, int max);
		unsigned int generate(unsigned int min, unsigned int max);
		float generate(float min, float max);
		glm::vec2 generate(const glm::vec2& min, const glm::vec2& max);
		glm::vec3 generate(const glm::vec3& min, const glm::vec3& max);
		glm::vec4 generate(const glm::vec4& min, const glm::vec4& max);
		glm::quat generate(const glm::quat& min, const glm::quat& max);
	};
}