#pragma once

#include "Confetti/Particle/MotionState.hpp"

#include <memory>

namespace cft
{
	class MotionBehavior
	{
	public:
		virtual ~MotionBehavior() = default;

		virtual std::unique_ptr<MotionBehavior> clone() const = 0;
		virtual glm::vec3 evaluate(float elapsedTime, const MotionState& motionState) = 0;
	};

	template <typename Derived>
	class CloneableMotionBehavior : public MotionBehavior
	{
	public:
		std::unique_ptr<MotionBehavior> clone() const override;
	};

	template<typename Derived>
	inline std::unique_ptr<MotionBehavior> CloneableMotionBehavior<Derived>::clone() const
	{
		return std::make_unique<Derived>(static_cast<const Derived&>(*this));
	}
}