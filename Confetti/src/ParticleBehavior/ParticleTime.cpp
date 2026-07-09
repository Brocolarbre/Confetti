#include "Confetti/ParticleBehavior/ParticleTime.hpp"

#include <glm/glm.hpp>

namespace cft
{
	float ParticleTime::normalize(float lifetime) const
	{
		float normalizedValue = value;

		if (space == Space::Absolute)
			normalizedValue = lifetime > 0.0f ? value / lifetime : 1.0f;

		return glm::clamp(normalizedValue, 0.0f, 1.0f);
	}

	ParticleTime ParticleTime::absolute(float value)
	{
		return ParticleTime{ value, Space::Absolute };
	}

	ParticleTime ParticleTime::normalized(float value)
	{
		return ParticleTime{ value, Space::Normalized };
	}
}