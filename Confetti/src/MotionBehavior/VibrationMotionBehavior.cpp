#include "Confetti/MotionBehavior/VibrationMotionBehavior.hpp"

namespace cft
{
	std::unique_ptr<MotionBehavior> VibrationMotionBehavior::clone() const
	{
		return std::make_unique<VibrationMotionBehavior>(*this);
	}

	void VibrationMotionBehavior::update(float elapsedTime, float deltaTime, Transform& transform)
	{
		static std::vector<glm::vec3> directions = {
			glm::vec3(-1.000000f,  0.000000f,  0.000000f),
			glm::vec3(0.823564f,  0.267261f,  0.500000f),
			glm::vec3(-0.408248f,  0.816497f,  0.408248f),
			glm::vec3(0.301511f, -0.904534f,  0.301511f),
			glm::vec3(0.577350f,  0.577350f,  0.577350f),
			glm::vec3(-0.666667f, -0.333333f,  0.666667f),
			glm::vec3(0.218218f,  0.872872f, -0.436436f),
			glm::vec3(-0.784465f,  0.588348f, -0.196116f),
			glm::vec3(0.147442f, -0.442326f, -0.884652f),
		};

		unsigned int directionIndex = static_cast<unsigned int>(elapsedTime * 10) % directions.size();
		transform.velocity = directions[directionIndex] * glm::vec3(5.0f);
	}
}