#include "Confetti/Behavior/Visual/ShrinkOutVisualBehavior.hpp"

namespace cft
{
	ShrinkOutVisualBehavior::ShrinkOutVisualBehavior(ParticleTime duration) :
		m_duration(duration)
	{

	}

	void ShrinkOutVisualBehavior::evaluate(float elapsedTime, float normalizedAge, ParticleView& particle)
	{
		float duration = m_duration.normalize(particle.lifetime);
		float start = 1.0f - duration;

		if (normalizedAge < start)
			return;

		float t = (normalizedAge - start) / duration;
		particle.scale = (1.0f - t) * particle.initialScale;
	}
}