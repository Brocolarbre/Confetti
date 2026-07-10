#include "Confetti/MotionBehavior/WrapPositionMotionBehavior.hpp"

namespace cft
{
	WrapPositionMotionBehavior::WrapPositionMotionBehavior(const glm::vec3& minimumPosition, const glm::vec3& maximumPosition) :
		m_minimumPosition(minimumPosition),
		m_maximumPosition(maximumPosition)
	{

	}

	std::unique_ptr<MotionBehavior> WrapPositionMotionBehavior::clone() const
	{
		return std::make_unique<WrapPositionMotionBehavior>(*this);
	}

	void WrapPositionMotionBehavior::update(float elapsedTime, float deltaTime, Transform& transform)
	{
		glm::vec3 size = m_maximumPosition - m_minimumPosition;

		for (unsigned int i = 0; i < 3; ++i)
		{
			while (transform.position[i] < m_minimumPosition[i])
				transform.position[i] += size[i];

			while (transform.position[i] > m_maximumPosition[i])
				transform.position[i] -= size[i];
		}
	}
}