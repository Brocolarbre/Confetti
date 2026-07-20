#include "Confetti/Emission/AttributeGenerator/Specialized/RandomNormalOffsetPositionGenerator.hpp"

namespace cft
{
	Position RandomNormalOffsetPositionGenerator::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
	{
		return context.position + context.normal * m_randomNumberGenerator.generate(m_minimumStrength, m_maximumStrength);
	}

	RandomNormalOffsetPositionGenerator::RandomNormalOffsetPositionGenerator(float minimumStrength, float maximumStrength, RandomNumberGenerator& randomNumberGenerator) :
		m_minimumStrength(minimumStrength),
		m_maximumStrength(maximumStrength),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	std::unique_ptr<AttributeGenerator<Position>> RandomNormalOffsetPositionGenerator::clone() const
	{
		return std::make_unique<RandomNormalOffsetPositionGenerator>(*this);
	}
}