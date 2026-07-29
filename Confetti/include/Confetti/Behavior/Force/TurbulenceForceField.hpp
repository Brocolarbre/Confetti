#pragma once

#include "ForceField.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	class CONFETTI_API TurbulenceForceField : public Cloneable<TurbulenceForceField, ForceField>
	{
	private:
		float m_strength;
		RandomNumberGenerator m_randomNumberGenerator;

	public:
		TurbulenceForceField(float strength, std::uint64_t seed = 0);

		std::optional<std::uint64_t> getSeed() const override;
		void setSeed(std::uint64_t seed) override;

		MotionAcceleration evaluate(const MotionState& motionState) override;
	};
}