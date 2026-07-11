#pragma once

#include "ForceField.hpp"

namespace cft
{
	class WindForceField : public ForceField
	{
	private:
		glm::vec3 m_velocity;
		float m_drag;

	public:
		WindForceField(const glm::vec3& direction, float strength, float drag);

		std::unique_ptr<ForceField> clone() const override;
		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}