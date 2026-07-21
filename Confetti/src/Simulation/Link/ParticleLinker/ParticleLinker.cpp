#include "Confetti/Simulation/Link/ParticleLinker/ParticleLinker.hpp"

#include <glm/glm.hpp>

namespace cft
{
	bool ParticleLinker::testLinkRules(const std::vector<std::unique_ptr<LinkRule>>& linkRules, const LinkContext& linkContext) const
	{
		for (const std::unique_ptr<LinkRule>& linkRule : linkRules)
		{
			if (!linkRule->test(linkContext))
				return false;
		}

		return true;
	}

	void ParticleLinker::createRibbon(unsigned int& createdRibbonsCount, RibbonPool& ribbonPool, unsigned int fromParticleId, unsigned int toParticleId, unsigned int ribbonRegistryId, unsigned int ribbonPointCount, float elapsedTime) const
	{
		ribbonPool.insert(Ribbon{ ribbonRegistryId, fromParticleId, toParticleId, elapsedTime, std::deque<PathPoint>(glm::max(ribbonPointCount, 2u), PathPoint{ {}, {}, {}, {}, elapsedTime }) });
		++createdRibbonsCount;
	}

	bool ParticleLinker::tryConnect(unsigned int& createdRibbonsCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int fromParticleId, unsigned int toParticleId, unsigned int ribbonRegistryId, unsigned int ribbonPointCount, float elapsedTime) const
	{
		if (fromParticleId == toParticleId)
			return false;

		if (ribbonPool.hasPointConnections(fromParticleId))
		{
			const std::unordered_set<unsigned int>& pointConnections = ribbonPool.getPointConnections(fromParticleId);
			if (pointConnections.find(toParticleId) != pointConnections.end())
				return false;
		}

		LinkContext linkContext{ particlePool.getParticleView(particlePool.getIndex(fromParticleId).value()), particlePool.getParticleView(particlePool.getIndex(toParticleId).value()), ribbonPool };
		if (!testLinkRules(m_connectionRules, linkContext))
			return false;

		createRibbon(createdRibbonsCount, ribbonPool, fromParticleId, toParticleId, ribbonRegistryId, ribbonPointCount, elapsedTime);
		return true;
	}

	ParticleLinker::ParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules) :
		m_connectionRules(std::move(connectionRules)),
		m_validationRules(std::move(validationRules))
	{

	}

	ParticleLinker::ParticleLinker(const ParticleLinker& particleLinker) :
		m_connectionRules(),
		m_validationRules()
	{
		m_connectionRules.reserve(particleLinker.m_connectionRules.size());
		for (const std::unique_ptr<LinkRule>& connectionRule : particleLinker.m_connectionRules)
			m_connectionRules.push_back(connectionRule->clone());

		m_validationRules.reserve(particleLinker.m_validationRules.size());
		for (const std::unique_ptr<LinkRule>& validationRule : particleLinker.m_validationRules)
			m_validationRules.push_back(validationRule->clone());
	}

	bool ParticleLinker::isRibbonValid(const LinkContext& linkContext) const
	{
		return testLinkRules(m_validationRules, linkContext);
	}
}