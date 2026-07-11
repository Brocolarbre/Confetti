#include "Confetti/ParticleBehavior/SquashStretchParticleBehavior.hpp"

namespace cft
{
	SquashStretchParticleBehavior::SquashStretchParticleBehavior(const glm::vec2& strength, float speed) :
		m_strength(strength),
		m_speed(speed)
	{

	}

	std::unique_ptr<ParticleBehavior> SquashStretchParticleBehavior::clone() const
	{
		return std::make_unique<SquashStretchParticleBehavior>(*this);
	}

	void SquashStretchParticleBehavior::evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle)
	{
		float stretch = std::sin(elapsedTime * m_speed + particle.phase);

		float horizontalScale = std::exp(-stretch * m_strength.x);
		float verticalScale = std::exp(stretch * m_strength.y);

		particle.scale = particle.initialScale * glm::vec3(horizontalScale, verticalScale, horizontalScale);
	}
}