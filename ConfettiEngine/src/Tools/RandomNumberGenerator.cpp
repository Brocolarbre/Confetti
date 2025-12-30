#include "ConfettiEngine/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	namespace
	{
		float mapRange(float value, float fromMin, float fromMax, float toMin, float toMax)
		{
			return (((value - fromMin) * (toMax - toMin)) / (fromMax - fromMin)) + toMin;
		}
	}

	RandomNumberGenerator::RandomNumberGenerator(unsigned int seed) :
		m_engine(seed),
		m_distribution(0.0f, 1.0f)
	{

	}

	float RandomNumberGenerator::generate(float min, float max)
	{
		return mapRange(m_distribution(m_engine), 0.0f, 1.0f, min, max);
	}

	glm::vec2 RandomNumberGenerator::generate(const glm::vec2& min, const glm::vec2& max)
	{
		return glm::vec2(generate(min.x, max.x), generate(min.y, max.y));
	}

	glm::vec3 RandomNumberGenerator::generate(const glm::vec3& min, const glm::vec3& max)
	{
		return glm::vec3(generate(min.x, max.x), generate(min.y, max.y), generate(min.z, max.z));
	}

	glm::vec4 RandomNumberGenerator::generate(const glm::vec4& min, const glm::vec4& max)
	{
		return glm::vec4(generate(min.x, max.x), generate(min.y, max.y), generate(min.z, max.z), generate(min.w, max.w));
	}
}