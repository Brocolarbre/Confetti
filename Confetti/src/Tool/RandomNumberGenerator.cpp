#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	RandomNumberGenerator::RandomNumberGenerator(unsigned int seed) :
		m_engine(seed),
		m_seed(seed),
		m_integerDistribution(),
		m_unsignedIntegerDistribution(),
		m_realDistribution()
	{

	}

	void RandomNumberGenerator::setSeed(unsigned int seed)
	{
		m_seed = seed;
		m_engine.seed(seed);
	}

	void RandomNumberGenerator::reset()
	{
		m_engine.seed(m_seed);

		m_integerDistribution.reset();
		m_unsignedIntegerDistribution.reset();
		m_realDistribution.reset();
	}

	int RandomNumberGenerator::generate(int min, int max)
	{
		return m_integerDistribution(m_engine, std::uniform_int_distribution<int>::param_type(min, max));
	}

	unsigned int RandomNumberGenerator::generate(unsigned int min, unsigned int max)
	{
		return m_unsignedIntegerDistribution(m_engine, std::uniform_int_distribution<unsigned int>::param_type(min, max));
	}

	float RandomNumberGenerator::generate(float min, float max)
	{
		return m_realDistribution(m_engine, std::uniform_real_distribution<float>::param_type(min, max));
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

	glm::quat RandomNumberGenerator::generate(const glm::quat& min, const glm::quat& max)
	{
		return glm::normalize(glm::slerp(min, max, generate(0.0f, 1.0f)));
	}
}