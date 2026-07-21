#include "Confetti/Simulation/Link/ParticleLinker/RandomParticleLinker.hpp"

namespace cft
{
	RandomParticleLinker::RandomParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules, unsigned int connectionsCount, RandomNumberGenerator& randomNumberGenerator) :
		Cloneable(std::move(connectionRules), std::move(validationRules)),
		m_connectionsCount(connectionsCount),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	unsigned int RandomParticleLinker::getMaximumRibbonCount(unsigned int maximumParticleCount) const
	{
		return std::max(m_connectionsCount, (maximumParticleCount * 3));
	}

	unsigned int RandomParticleLinker::createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime)
	{
		unsigned int poolCount = static_cast<unsigned int>(particlePool.getCount());
		unsigned int createdRibbonsCount = 0;

		const std::vector<unsigned int>& particleId = particlePool.getId();

		for (unsigned int i = 0; i < m_connectionsCount; ++i)
		{
			unsigned int randomIndexFrom = m_randomNumberGenerator.generateInteger(0, static_cast<int>(poolCount) - 1);
			unsigned int randomIndexTo = m_randomNumberGenerator.generateInteger(0, static_cast<int>(poolCount) - 1);

			tryConnect(createdRibbonsCount, ribbonPool, particlePool, particleId[randomIndexFrom], particleId[randomIndexTo], ribbonRegistryId, ribbonPointCount, elapsedTime);
		}

		return createdRibbonsCount;
	}
}