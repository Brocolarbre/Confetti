#pragma once

#include "ForceField.hpp"

namespace cft
{
	class CONFETTI_API FollowTargetForceField : public Cloneable<FollowTargetForceField, ForceField>
	{
	private:
		std::function<glm::vec3()> m_targetProvider;
		float m_spring;
		float m_damping;

	public:
		FollowTargetForceField(std::function<glm::vec3()> targetProvider, float responseTime, float dampingRatio);

		MotionAcceleration evaluate(const MotionState& motionState) override;
	};
}