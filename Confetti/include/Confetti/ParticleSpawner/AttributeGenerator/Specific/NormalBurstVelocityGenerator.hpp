#pragma once

#include "Confetti/ParticleSpawner/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/ParticleSpawner/AttributeGenerator/AttributeTypes.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class NormalBurstVelocityGenerator : public AttributeGenerator<Velocity>
	{
	private:
		float m_strength;
		float m_maximumAngle;
		RandomNumberGenerator& m_randomNumberGenerator;

		Velocity generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		NormalBurstVelocityGenerator(float strength, float maximumAngle, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<AttributeGenerator<Velocity>> clone() const override;
	};
}