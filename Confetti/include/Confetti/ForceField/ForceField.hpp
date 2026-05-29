#pragma once

#include <glm/glm.hpp>
#include <memory>

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

		virtual std::unique_ptr<ForceField> clone() const = 0;
		virtual glm::vec3 apply(const glm::vec3& position, float elapsedTime, float deltaTime) const = 0;
	};
}