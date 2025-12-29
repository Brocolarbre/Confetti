#pragma once

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

		float operator()(float min, float max);
	};
}