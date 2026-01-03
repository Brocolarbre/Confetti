#pragma once

#include <glm/glm.hpp>

namespace cft
{
	class ForceField
	{
	public:
		virtual ~ForceField() = default;

		virtual glm::vec3 apply(const glm::vec3& velocity, float elapsedTime, float deltaTime) const = 0;
	};
}