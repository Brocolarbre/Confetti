#include "Confetti/Simulation/Link/ParticleLinker/KNearestNeighborParticleLinker.hpp"

#include <algorithm>

namespace cft
{
	KNearestNeighborParticleLinker::KNearestNeighborParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules, unsigned int neighborCount) :
		Cloneable(std::move(connectionRules), std::move(validationRules)),
		m_neighborCount(neighborCount)
	{

	}

	unsigned int KNearestNeighborParticleLinker::createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime)
	{
		unsigned int createdRibbonsCount = 0;

		const std::vector<unsigned int>& particleId = particlePool.getId();
		const std::vector<glm::vec3>& particlePostBehaviorPosition = particlePool.getPostBehaviorPosition();

		unsigned int particlePoolCount = particlePool.getCount();

		for (unsigned int fromIndex = 0; fromIndex < particlePoolCount; ++fromIndex)
		{
			std::vector<std::pair<float, unsigned int>> candidates;

			unsigned int fromParticleId = particleId[fromIndex];

			for (unsigned int toIndex = 0; toIndex < particlePoolCount; ++toIndex)
			{
				unsigned int toParticleId = particleId[toIndex];

				if (!canConnect(ribbonPool, particlePool, fromParticleId, toParticleId, elapsedTime))
					continue;

				glm::vec3 delta = particlePostBehaviorPosition[fromIndex] - particlePostBehaviorPosition[toIndex];
				float distanceSquared = glm::dot(delta, delta);

				candidates.emplace_back(distanceSquared, toIndex);
			}

			std::sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) {
				return a.first < b.first;
			});

			unsigned int neighborCount = glm::min(static_cast<unsigned int>(candidates.size()), m_neighborCount);

			for (unsigned int i = 0; i < neighborCount; ++i)
				createRibbon(createdRibbonsCount, ribbonPool, fromParticleId, particleId[candidates[i].second], ribbonRegistryId, ribbonPointCount, elapsedTime);
		}

		return createdRibbonsCount;
	}
}