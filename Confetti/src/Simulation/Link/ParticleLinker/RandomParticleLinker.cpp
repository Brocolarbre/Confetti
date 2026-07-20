#include "Confetti/Simulation/Link/ParticleLinker/RandomParticleLinker.hpp"

namespace cft
{
	RandomParticleLinker::RandomParticleLinker(float maximumDistance, unsigned int connectionsCount, RandomNumberGenerator& randomNumberGenerator) :
		m_maximumDistance(maximumDistance * maximumDistance),
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

		const std::vector<glm::vec3>& particlePosition = particlePool.getPosition();
		const std::vector<unsigned int>& particleId = particlePool.getId();

		for (unsigned int i = 0; i < m_connectionsCount; ++i)
		{
			unsigned int randomIndexFrom = m_randomNumberGenerator.generateInteger(0, static_cast<int>(poolCount) - 1);
			const std::unordered_set<unsigned int>& pointConnections = ribbonPool.getPointConnections(particleId[randomIndexFrom]);

			unsigned int randomIndexTo = m_randomNumberGenerator.generateInteger(0, static_cast<int>(poolCount) - 1);

			if (randomIndexFrom != randomIndexTo && pointConnections.find(particleId[randomIndexTo]) == pointConnections.end())
			{
				if (pointConnections.size() < 3 && ribbonPool.getPointConnections(particleId[randomIndexTo]).size() < 3)
				{
					ribbonPool.insert(Ribbon{ ribbonRegistryId, particleId[randomIndexFrom], particleId[randomIndexTo], elapsedTime, std::deque<PathPoint>(glm::max(ribbonPointCount, 2u), PathPoint{ {}, {}, {}, {}, elapsedTime }) });
					++createdRibbonsCount;
				}
			}
		}

		return createdRibbonsCount;
	}

	bool RandomParticleLinker::isRibbonValid(const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const
	{
		glm::vec3 delta = fromParticle.postBehaviorPosition - toParticle.postBehaviorPosition;
		return glm::dot(delta, delta) <= m_maximumDistance;
	}
}