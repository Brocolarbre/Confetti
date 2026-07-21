#include "Confetti/Simulation/Link/ParticleLinker/TargetParticleLinker.hpp"

namespace cft
{
	TargetParticleLinker::TargetParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules, unsigned int targetParticleId) :
		Cloneable(std::move(connectionRules), std::move(validationRules)),
		m_targetParticleId(targetParticleId)
	{

	}

	unsigned int TargetParticleLinker::createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime)
	{
		unsigned int createdRibbonsCount = 0;

		std::optional<unsigned int> targetIndex = particlePool.getIndex(m_targetParticleId);
		if (!targetIndex.has_value())
			return createdRibbonsCount;

		const std::vector<unsigned int>& particleId = particlePool.getId();

		unsigned int particlePoolCount = particlePool.getCount();

		for (unsigned int i = 0; i < particlePoolCount; ++i)
		{
			unsigned int fromParticleId = particleId[i];
			if (fromParticleId == m_targetParticleId)
				continue;

			if (canConnect(ribbonPool, particlePool, fromParticleId, m_targetParticleId, elapsedTime))
				createRibbon(createdRibbonsCount, ribbonPool, fromParticleId, m_targetParticleId, ribbonRegistryId, ribbonPointCount, elapsedTime);
		}

		return createdRibbonsCount;
	}
}