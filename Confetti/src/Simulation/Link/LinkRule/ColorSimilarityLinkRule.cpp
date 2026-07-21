#include "Confetti/Simulation/Link/LinkRule/ColorSimilarityLinkRule.hpp"

namespace cft
{
	ColorSimilarityLinkRule::ColorSimilarityLinkRule(float threshold) :
		m_threshold(threshold)
	{

	}

	bool ColorSimilarityLinkRule::test(const LinkContext& linkContext) const
	{
		float distance = glm::distance(linkContext.fromParticle.color, linkContext.toParticle.color);
		return distance < m_threshold;
	}
}