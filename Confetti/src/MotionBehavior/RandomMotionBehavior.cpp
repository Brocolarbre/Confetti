#include "Confetti/MotionBehavior/RandomMotionBehavior.hpp"

namespace cft
{
	std::unique_ptr<MotionBehavior> RandomMotionBehavior::clone() const
	{
		return std::make_unique<RandomMotionBehavior>(*this);
	}

	void RandomMotionBehavior::update(float elapsedTime, float deltaTime, Transform& transform)
	{
		//float radius = 5.0f;
		//float progress = elapsedTime * 2.0f;
		//transform.position = glm::vec3(glm::cos(progress) * radius, progress, glm::sin(progress) * radius);
		float t = elapsedTime;
		float scale = 10.0f;

		transform.position.x = scale * sin(t);
		transform.position.z = 0.0f;
		transform.position.y = scale * sin(t) * cos(t) * 0.5f;
	}
}