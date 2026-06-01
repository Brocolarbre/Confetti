#pragma once

#include "ForceField.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class JitterForceField : public ForceField
	{
	private:
		float m_strength;
		RandomNumberGenerator& m_randomNumberGenerator;

	public:
		JitterForceField(float strength, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<ForceField> clone() const override;
		glm::vec3 apply(float elapsedTime, const Transform& transform) const override;
	};
}