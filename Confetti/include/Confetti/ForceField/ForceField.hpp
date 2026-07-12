#pragma once

#include "Confetti/Particle/MotionState.hpp"

#include <memory>

namespace cft
{
	struct MotionAcceleration
	{
		glm::vec3 linear;
		glm::vec3 angular;
	};

	class ForceField
	{
	public:
		virtual ~ForceField() = default;

		virtual std::unique_ptr<ForceField> clone() const = 0;
		virtual MotionAcceleration evaluate(const MotionState& motionState) const = 0;
	};

	template <typename Derived>
	class CloneableForceField : public ForceField
	{
	public:
		std::unique_ptr<ForceField> clone() const override;
	};

	template<typename Derived>
	inline std::unique_ptr<ForceField> CloneableForceField<Derived>::clone() const
	{
		return std::make_unique<Derived>(static_cast<const Derived&>(*this));
	}
}