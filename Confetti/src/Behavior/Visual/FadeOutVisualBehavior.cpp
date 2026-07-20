#include "Confetti/Behavior/Visual/FadeOutVisualBehavior.hpp"

namespace cft
{
	FadeOutVisualBehavior::FadeOutVisualBehavior(ParticleTime duration) :
		m_duration(duration)
	{

	}

	void FadeOutVisualBehavior::evaluate(float elapsedTime, float normalizedAge, ParticleView& particle)
	{
		float duration = m_duration.normalize(particle.lifetime);
		float start = 1.0f - duration;

		if (normalizedAge < start)
			return;

		float t = (normalizedAge - start) / duration;
		particle.color.a = (1.0f - t) * particle.initialColor.a;
	}
}