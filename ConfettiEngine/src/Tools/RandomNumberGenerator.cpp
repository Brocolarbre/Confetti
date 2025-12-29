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

	float RandomNumberGenerator::operator()(float min, float max)
	{
		return mapRange(m_distribution(m_engine), 0.0f, 1.0f, min, max);
	}
}