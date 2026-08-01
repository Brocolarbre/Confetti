#pragma once

#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Emission/AttributeGenerator/AttributeTypes.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	class CONFETTI_API NormalBurstLinearVelocityGenerator : public Cloneable<NormalBurstLinearVelocityGenerator, AttributeGenerator<LinearVelocity>>
	{
	private:
		float m_strength;
		float m_maximumAngle;
		RandomNumberGenerator m_randomNumberGenerator;

		LinearVelocity generateValue(unsigned int count, unsigned int index, const SpawnContext& context, float elapsedTime) override;

	public:
		NormalBurstLinearVelocityGenerator(float strength, float maximumAngle, std::uint64_t seed = 0);

		std::optional<std::uint64_t> getSeed() const override;
		void setSeed(std::uint64_t seed) override;
	};
}