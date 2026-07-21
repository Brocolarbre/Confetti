#include "Confetti/Simulation/Link/LinkRule/AgeSimilarityLinkRule.hpp"

namespace cft
{
	AgeSimilarityLinkRule::AgeSimilarityLinkRule(float threshold) :
		m_threshold(threshold)
	{

	}

	bool AgeSimilarityLinkRule::test(const LinkContext& linkContext) const
	{
		float fromAge = linkContext.elapsedTime - linkContext.fromParticle.spawnTime;
		float toAge = linkContext.elapsedTime - linkContext.toParticle.spawnTime;

		return glm::abs(fromAge - toAge) < m_threshold;
	}
}