#pragma once

#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Emission/AttributeGenerator/AttributeTypes.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	class NormalBurstLinearVelocityGenerator : public AttributeGenerator<LinearVelocity>
	{
	private:
		float m_strength;
		float m_maximumAngle;
		RandomNumberGenerator& m_randomNumberGenerator;

		LinearVelocity generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		NormalBurstLinearVelocityGenerator(float strength, float maximumAngle, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<AttributeGenerator<LinearVelocity>> clone() const override;
	};
}