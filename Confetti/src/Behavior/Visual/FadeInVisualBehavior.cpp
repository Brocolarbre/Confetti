#include "Confetti/Behavior/Visual/FadeInVisualBehavior.hpp"

namespace cft
{
	FadeInVisualBehavior::FadeInVisualBehavior(ParticleTime duration) :
		m_duration(duration)
	{

	}

	void FadeInVisualBehavior::evaluate(float elapsedTime, float normalizedAge, ParticleView& particle)
	{
		float end = m_duration.normalize(particle.lifetime);

		if (normalizedAge > end)
			return;

		float t = glm::min(normalizedAge / end, 1.0f);
		particle.color.a = t * particle.initialColor.a;
	}
}