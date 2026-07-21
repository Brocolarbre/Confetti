#include "Confetti/Simulation/Link/LinkRule/DistanceLinkRule.hpp"

namespace cft
{
	DistanceLinkRule::DistanceLinkRule(float minimumDistance, float maximumDistance) :
		m_squaredMinimumDistance(minimumDistance * minimumDistance),
		m_squaredMaximumDistance(maximumDistance * maximumDistance)
	{

	}

	bool DistanceLinkRule::test(const LinkContext& linkContext) const
	{
		glm::vec3 delta = linkContext.fromParticle.postBehaviorPosition - linkContext.toParticle.postBehaviorPosition;
		float squaredDistance = glm::dot(delta, delta);

		return squaredDistance >= m_squaredMinimumDistance && squaredDistance <= m_squaredMaximumDistance;
	}
}