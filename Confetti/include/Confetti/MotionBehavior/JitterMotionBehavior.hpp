#pragma once

#include "MotionBehavior.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class JitterMotionBehavior : public Cloneable<JitterMotionBehavior, MotionBehavior>
	{
	private:
		float m_strength;
		RandomNumberGenerator& m_randomNumberGenerator;

	public:
		JitterMotionBehavior(float strength, RandomNumberGenerator& randomNumberGenerator);

		glm::vec3 evaluate(float age, const MotionState& motionState) override;
	};
}