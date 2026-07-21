#include "Confetti/Simulation/Link/ParticleLinker/ChainParticleLinker.hpp"

#include <algorithm>
#include <numeric>

namespace cft
{
	ChainParticleLinker::ChainParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules) :
		Cloneable(std::move(connectionRules), std::move(validationRules))
	{

	}

	unsigned int ChainParticleLinker::createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime)
	{
		unsigned int createdRibbonsCount = 0;

		std::vector<unsigned int> indices(particlePool.getCount());
		std::iota(indices.begin(), indices.end(), 0);

		const std::vector<float>& particleSpawnTime = particlePool.getSpawnTime();

		std::sort(indices.begin(), indices.end(), [&](unsigned int a, unsigned int b) {
			return particleSpawnTime[a] < particleSpawnTime[b];
		});

		const std::vector<unsigned int>& particleId = particlePool.getId();

		unsigned int particlePoolCount = particlePool.getCount();

		for (unsigned int i = 0; i < indices.size(); ++i)
		{
			unsigned int fromParticleId = particleId[indices[i]];
			unsigned int toParticleId = particleId[indices[i + 1]];

			if (canConnect(ribbonPool, particlePool, fromParticleId, toParticleId, elapsedTime))
				createRibbon(createdRibbonsCount, ribbonPool, fromParticleId, toParticleId, ribbonRegistryId, ribbonPointCount, elapsedTime);
		}

		return createdRibbonsCount;
	}
}