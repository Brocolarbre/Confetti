#include "Confetti/Simulation/Link/LinkRule/VelocitySimilarityLinkRule.hpp"

namespace cft
{
	VelocitySimilarityLinkRule::VelocitySimilarityLinkRule(float threshold) :
		m_threshold(threshold)
	{

	}

	bool VelocitySimilarityLinkRule::test(const LinkContext& linkContext) const
	{
		float alignment = glm::dot(glm::normalize(linkContext.fromParticle.linearVelocity), glm::normalize(linkContext.toParticle.linearVelocity));
		return alignment > m_threshold;
	}
}