#pragma once

#include "MotionBehavior.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class JitterMotionBehavior : public CloneableMotionBehavior<JitterMotionBehavior>
	{
	private:
		float m_strength;
		RandomNumberGenerator& m_randomNumberGenerator;

	public:
		JitterMotionBehavior(float strength, RandomNumberGenerator& randomNumberGenerator);

		glm::vec3 evaluate(float elapsedTime, const MotionState& motionState) override;
	};
}