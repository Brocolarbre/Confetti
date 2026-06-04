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

	void SquashStretchParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		float stretch = std::sin(elapsedTime * m_speed);

		//float verticalScale = glm::max(1.0f + stretch * m_strength.y, 0.5f);
		//float horizontalScale = 1.0f / verticalScale;
		float horizontalScale = std::exp(-stretch * m_strength.x);
		float verticalScale = std::exp(stretch * m_strength.y);
		//float horizontalScale = 1.0f / verticalScale;

		particle.scale = particle.initialScale * glm::vec2(horizontalScale, verticalScale);
	}
}