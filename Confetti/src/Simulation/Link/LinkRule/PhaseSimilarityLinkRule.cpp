#include "Confetti/Simulation/Link/LinkRule/PhaseSimilarityLinkRule.hpp"

namespace cft
{
	PhaseSimilarityLinkRule::PhaseSimilarityLinkRule(float threshold) :
		m_threshold(threshold)
	{

	}

	bool PhaseSimilarityLinkRule::test(const LinkContext& linkContext) const
	{
		return glm::abs(linkContext.fromParticle.phase - linkContext.toParticle.phase) < m_threshold;
	}
}