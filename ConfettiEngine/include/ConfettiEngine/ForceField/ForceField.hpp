#pragma once

#include <glm/glm.hpp>

namespace cft
{
	/*enum class Falloff
	{
		Constant,
		Linear,
		Quadratic
	};*/

	class ForceField
	{
	public:
		virtual ~ForceField() = default;

		virtual glm::vec3 apply(const glm::vec3& velocity, const glm::vec3& position, float elapsedTime, float deltaTime) const = 0;
	};
}