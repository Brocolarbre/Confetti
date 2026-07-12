#pragma once

#include "ForceField.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class TurbulenceForceField : public CloneableForceField<TurbulenceForceField>
	{
	private:
		float m_strength;
		RandomNumberGenerator& m_randomNumberGenerator;

	public:
		TurbulenceForceField(float strength, RandomNumberGenerator& randomNumberGenerator);

		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}