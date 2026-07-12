#pragma once

#include "ForceField.hpp"

namespace cft
{
	class DirectionalForceField : public Cloneable<DirectionalForceField, ForceField>
	{
	private:
		glm::vec3 m_direction;
		float m_strength;

	public:
		DirectionalForceField(const glm::vec3& direction, float strength);

		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}