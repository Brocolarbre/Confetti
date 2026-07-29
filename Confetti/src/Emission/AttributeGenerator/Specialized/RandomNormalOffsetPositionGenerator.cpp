#include "Confetti/Emission/AttributeGenerator/Specialized/RandomNormalOffsetPositionGenerator.hpp"

namespace cft
{
	Position RandomNormalOffsetPositionGenerator::generateValue(unsigned int count, unsigned int index, const SpawnContext& context)
	{
		return context.position + context.normal * m_randomNumberGenerator.generate(m_minimumStrength, m_maximumStrength);
	}

	RandomNormalOffsetPositionGenerator::RandomNormalOffsetPositionGenerator(float minimumStrength, float maximumStrength, std::uint64_t seed) :
		m_minimumStrength(minimumStrength),
		m_maximumStrength(maximumStrength),
		m_randomNumberGenerator(seed)
	{

	}

	std::optional<std::uint64_t> RandomNormalOffsetPositionGenerator::getSeed() const
	{
		return m_randomNumberGenerator.getSeed();
	}

	void RandomNormalOffsetPositionGenerator::setSeed(std::uint64_t seed)
	{
		m_randomNumberGenerator.setSeed(seed);
	}
}