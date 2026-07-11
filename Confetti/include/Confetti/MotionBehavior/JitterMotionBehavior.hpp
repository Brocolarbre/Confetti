#pragma once

#include "MotionBehavior.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class JitterMotionBehavior : public MotionBehavior
	{
	private:
		float m_strength;
		RandomNumberGenerator& m_randomNumberGenerator;

	public:
		JitterMotionBehavior(float strength, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<MotionBehavior> clone() const override;
		glm::vec3 evaluate(float elapsedTime, const MotionState& motionState) override;
	};
}