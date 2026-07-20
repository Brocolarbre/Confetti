#pragma once

#include "ForceField.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	class TurbulenceForceField : public Cloneable<TurbulenceForceField, ForceField>
	{
	private:
		float m_strength;
		RandomNumberGenerator& m_randomNumberGenerator;

	public:
		TurbulenceForceField(float strength, RandomNumberGenerator& randomNumberGenerator);

		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}