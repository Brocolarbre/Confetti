#include "Confetti/Simulation/Link/RandomParticleLinker.hpp"

namespace cft
{
	RandomParticleLinker::RandomParticleLinker(float maximumDistance, unsigned int connectionsCount, RandomNumberGenerator& randomNumberGenerator) :
		m_maximumDistance(maximumDistance * maximumDistance),
		m_connectionsCount(connectionsCount),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	unsigned int RandomParticleLinker::createRibbons(RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime)
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
					ribbonPool.insert(Ribbon{ ribbonRegistryId, particleId[randomIndexFrom], particleId[randomIndexTo], elapsedTime, std::deque<PathPoint>(5, PathPoint{ {}, {}, {}, {}, elapsedTime }) });
					++createdRibbonsCount;
				}
			}
		}

		return createdRibbonsCount;
	}

	void RandomParticleLinker::updateRibbon(RibbonView& ribbon, const PathConfiguration& pathConfiguration, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle)
	{
		ribbon.points[0] = PathPoint{ glm::vec4{}, fromParticle.postBehaviorPosition, 0.0f, 0.0f, ribbon.points[0].spawnTime };
		ribbon.points[1] = PathPoint{ glm::vec4{}, toParticle.postBehaviorPosition, 0.0f, 1.0f, ribbon.points[1].spawnTime };

		float length = glm::distance(fromParticle.postBehaviorPosition, toParticle.postBehaviorPosition);

		for (unsigned int i = 0; i < ribbon.points.size(); ++i)
		{
			float t = static_cast<float>(i) / static_cast<float>(ribbon.points.size() - 1);
			ribbon.points[i].position = glm::mix(fromParticle.postBehaviorPosition, toParticle.postBehaviorPosition, t);
			ribbon.points[i].distanceOnTrail = length * t;
		}
	}

	bool RandomParticleLinker::isRibbonValid(const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const
	{
		glm::vec3 delta = fromParticle.postBehaviorPosition - toParticle.postBehaviorPosition;
		return glm::dot(delta, delta) <= m_maximumDistance;
	}
}