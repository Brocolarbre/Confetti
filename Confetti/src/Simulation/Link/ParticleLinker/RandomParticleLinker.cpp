#include "Confetti/Simulation/Link/ParticleLinker/RandomParticleLinker.hpp"

namespace cft
{
	RandomParticleLinker::RandomParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules, unsigned int connectionCount, RandomNumberGenerator& randomNumberGenerator) :
		Cloneable(std::move(connectionRules), std::move(validationRules)),
		m_connectionCount(connectionCount),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	unsigned int RandomParticleLinker::createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime)
	{
		unsigned int createdRibbonsCount = 0;

		int maximumParticlePoolIndex = static_cast<int>(particlePool.getCount()) - 1;
		const std::vector<unsigned int>& particleId = particlePool.getId();

		unsigned int connectionCount = glm::min(m_connectionCount, particlePool.getCount());

		for (unsigned int i = 0; i < connectionCount; ++i)
		{
			unsigned int randomIndexFrom = m_randomNumberGenerator.generateInteger(0, maximumParticlePoolIndex);
			unsigned int randomIndexTo = m_randomNumberGenerator.generateInteger(0, maximumParticlePoolIndex);

			if (canConnect(ribbonPool, particlePool, particleId[randomIndexFrom], particleId[randomIndexTo], elapsedTime))
				createRibbon(createdRibbonsCount, ribbonPool, particleId[randomIndexFrom], particleId[randomIndexTo], ribbonRegistryId, ribbonPointCount, elapsedTime);
		}

		return createdRibbonsCount;
	}
}