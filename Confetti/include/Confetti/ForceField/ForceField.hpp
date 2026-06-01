#pragma once

#include "Confetti/Particle/Transform.hpp"

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
		virtual glm::vec3 apply(float elapsedTime, float deltaTime, const Transform& transform) const = 0;
	};
}