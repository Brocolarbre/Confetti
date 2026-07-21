#include "Confetti/Simulation/Link/LinkRule/ConnectionLinkRule.hpp"

namespace cft
{
	ConnectionLinkRule::ConnectionLinkRule(unsigned int maximumConnectionCount) :
		m_maximumConnectionCount(maximumConnectionCount)
	{

	}

	bool ConnectionLinkRule::test(const LinkContext& linkContext) const
	{
		if (linkContext.ribbonPool.hasPointConnections(linkContext.fromParticle.id) && linkContext.ribbonPool.getPointConnections(linkContext.fromParticle.id).size() >= m_maximumConnectionCount)
			return false;

		if (linkContext.ribbonPool.hasPointConnections(linkContext.toParticle.id) && linkContext.ribbonPool.getPointConnections(linkContext.toParticle.id).size() >= m_maximumConnectionCount)
			return false;

		return true;
	}
}