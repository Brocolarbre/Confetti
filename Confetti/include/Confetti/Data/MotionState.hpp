#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace cft
{
	struct MotionState
	{
		glm::vec3 position;
		glm::vec3 linearVelocity;
		glm::quat rotation;
		glm::vec3 angularVelocity;
	};
}