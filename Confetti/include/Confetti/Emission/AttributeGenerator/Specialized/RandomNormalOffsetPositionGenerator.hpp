#pragma once

#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Emission/AttributeGenerator/AttributeTypes.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	class CONFETTI_API RandomNormalOffsetPositionGenerator : public Cloneable<RandomNormalOffsetPositionGenerator, AttributeGenerator<Position>>
	{
	private:
		float m_minimumStrength;
		float m_maximumStrength;
		RandomNumberGenerator m_randomNumberGenerator;

		Position generateValue(unsigned int count, unsigned int index, const SpawnContext& context) override;

	public:
		RandomNormalOffsetPositionGenerator(float minimumStrength, float maximumStrength, std::uint64_t seed = 0);

		std::optional<std::uint64_t> getSeed() const override;
		void setSeed(std::uint64_t seed) override;
	};
}