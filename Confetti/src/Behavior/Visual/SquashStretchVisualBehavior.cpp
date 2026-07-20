#include "Confetti/Behavior/Visual/SquashStretchVisualBehavior.hpp"

namespace cft
{
	SquashStretchVisualBehavior::SquashStretchVisualBehavior(const glm::vec2& strength, float speed) :
		m_strength(strength),
		m_speed(speed)
	{

	}

	void SquashStretchVisualBehavior::evaluate(float elapsedTime, float normalizedAge, ParticleView& particle)
	{
		float stretch = std::sin(elapsedTime * m_speed + particle.phase);

		float horizontalScale = std::exp(-stretch * m_strength.x);
		float verticalScale = std::exp(stretch * m_strength.y);

		particle.scale = particle.initialScale * glm::vec3(horizontalScale, verticalScale, horizontalScale);
	}
}