#include "Confetti/Simulation/Link/ParticleLinker/OriginParticleLinker.hpp"

namespace cft
{
	OriginParticleLinker::OriginParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules, const glm::vec3& origin) :
		Cloneable(std::move(connectionRules), std::move(validationRules)),
		m_origin(origin)
	{

	}

	unsigned int OriginParticleLinker::createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime)
	{
		unsigned int createdRibbonsCount = 0;

		const std::vector<glm::vec3>& particlePostBehaviorPosition = particlePool.getPostBehaviorPosition();
		const std::vector<unsigned int>& particleId = particlePool.getId();

		unsigned int particlePoolCount = particlePool.getCount();

		unsigned int originIndex = 0;
		float bestDistance = std::numeric_limits<float>::max();

		for (unsigned int i = 0; i < particlePoolCount; ++i)
		{
			glm::vec3 delta = particlePostBehaviorPosition[i] - m_origin;
			float distance = glm::dot(delta, delta);

			if (distance < bestDistance)
			{
				bestDistance = distance;
				originIndex = i;
			}
		}

		unsigned int originId = particleId[originIndex];

		for (unsigned int i = 0; i < particlePool.getCount(); ++i)
		{
			if (i == originIndex)
				continue;

			if (canConnect(ribbonPool, particlePool, particleId[i], originId, elapsedTime))
				createRibbon(createdRibbonsCount, ribbonPool, particleId[i], originId, ribbonRegistryId, ribbonPointCount, elapsedTime);
		}

		return createdRibbonsCount;
	}
}