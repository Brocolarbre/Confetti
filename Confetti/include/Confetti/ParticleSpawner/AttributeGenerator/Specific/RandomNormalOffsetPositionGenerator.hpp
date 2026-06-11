#pragma once

#include "Confetti/ParticleSpawner/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/ParticleSpawner/AttributeGenerator/AttributeTypes.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class RandomNormalOffsetPositionGenerator : public AttributeGenerator<Position>
	{
	private:
		float m_minimumStrength;
		float m_maximumStrength;
		RandomNumberGenerator& m_randomNumberGenerator;

		Position generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		RandomNormalOffsetPositionGenerator(float minimumStrength, float maximumStrength, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<AttributeGenerator<Position>> clone() const override;
	};
}