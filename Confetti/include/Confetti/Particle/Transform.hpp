#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace cft
{
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 velocity;
		glm::quat rotation;
		glm::vec3 angularVelocity;
	};
}