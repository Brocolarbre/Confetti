#pragma once

#include "ForceField.hpp"

namespace cft
{
	class DirectionalForceField : public CloneableForceField<DirectionalForceField>
	{
	private:
		glm::vec3 m_direction;
		float m_strength;

	public:
		DirectionalForceField(const glm::vec3& direction, float strength);

		MotionAcceleration evaluate(const MotionState& motionState) const override;
	};
}