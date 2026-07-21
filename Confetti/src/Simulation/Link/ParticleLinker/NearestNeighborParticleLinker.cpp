#include "Confetti/Simulation/Link/ParticleLinker/NearestNeighborParticleLinker.hpp"

#include <limits>

namespace cft
{
	NearestNeighborParticleLinker::NearestNeighborParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules) :
		Cloneable(std::move(connectionRules), std::move(validationRules))
	{

	}

	unsigned int NearestNeighborParticleLinker::createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime)
	{
		unsigned int createdRibbonsCount = 0;

		const std::vector<unsigned int>& particleId = particlePool.getId();
		const std::vector<glm::vec3>& particlePostBehaviorPosition = particlePool.getPostBehaviorPosition();

		unsigned int particlePoolCount = particlePool.getCount();

		for (unsigned int fromIndex = 0; fromIndex < particlePoolCount; ++fromIndex)
		{
			unsigned int fromParticleId = particleId[fromIndex];

			int nearestIndex = -1;
			float nearestDistanceSquared = std::numeric_limits<float>::max();

			for (unsigned int toIndex = 0; toIndex < particlePoolCount; ++toIndex)
			{
				unsigned int toParticleId = particleId[toIndex];

				if (!canConnect(ribbonPool, particlePool, fromParticleId, toParticleId, elapsedTime))
					continue;

				glm::vec3 delta = particlePostBehaviorPosition[fromIndex] - particlePostBehaviorPosition[toIndex];
				float distanceSquared = glm::dot(delta, delta);

				if (distanceSquared < nearestDistanceSquared)
				{
					nearestDistanceSquared = distanceSquared;
					nearestIndex = static_cast<int>(toIndex);
				}
			}

			if (nearestIndex >= 0)
				createRibbon(createdRibbonsCount, ribbonPool, particleId[fromIndex], particleId[nearestIndex], ribbonRegistryId, ribbonPointCount, elapsedTime);
		}

		return createdRibbonsCount;
	}
}