#pragma once

#include "MotionBehavior.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	class CONFETTI_API JitterMotionBehavior : public Cloneable<JitterMotionBehavior, MotionBehavior>
	{
	private:
		float m_strength;
		RandomNumberGenerator m_randomNumberGenerator;

	public:
		JitterMotionBehavior(float strength, std::uint64_t seed = 0);

		std::optional<std::uint64_t> getSeed() const override;
		void setSeed(std::uint64_t seed) override;

		glm::vec3 evaluate(float age, const MotionState& motionState) override;
	};
}