#pragma once

#include <glm/glm.hpp>

namespace cft
{
	struct View
	{
		const glm::vec3& position;
		const glm::vec3& right;
		const glm::vec3& up;
		const glm::vec3& forward;
		const glm::mat4& viewMatrix;
		const glm::mat4& projectionMatrix;
	};
}