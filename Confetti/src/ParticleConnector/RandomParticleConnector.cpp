#include "Confetti/ParticleConnector/RandomParticleConnector.hpp"

namespace cft
{
	RandomParticleConnector::RandomParticleConnector(float maximumDistance, unsigned int connexionsCount, RandomNumberGenerator& randomNumberGenerator) :
		m_maximumDistance(maximumDistance * maximumDistance),
		m_connexionsCount(connexionsCount),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	unsigned int RandomParticleConnector::createRibbons(RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime)
	{
		unsigned int poolCount = static_cast<unsigned int>(particlePool.getCount());
		unsigned int createdRibbonsCount = 0;

		const std::vector<glm::vec3>& particlePosition = particlePool.getPosition();
		const std::vector<unsigned int>& particleId = particlePool.getId();

		for (unsigned int i = 0; i < m_connexionsCount; ++i)
		{
			unsigned int randomIndexFrom = m_randomNumberGenerator.generateInteger(0, static_cast<int>(poolCount) - 1);
			const std::unordered_set<unsigned int>& pointConnexions = ribbonPool.getPointConnexions(particleId[randomIndexFrom]);

			unsigned int randomIndexTo = m_randomNumberGenerator.generateInteger(0, static_cast<int>(poolCount) - 1);

			if (randomIndexFrom != randomIndexTo && pointConnexions.find(particleId[randomIndexTo]) == pointConnexions.end())
			{
				if (pointConnexions.size() < 3 && ribbonPool.getPointConnexions(particleId[randomIndexTo]).size() < 3)
				{
					ribbonPool.insert(Ribbon{ ribbonRegistryId, particleId[randomIndexFrom], particleId[randomIndexTo], elapsedTime, std::deque<TrailPoint>(5, TrailPoint{ {}, {}, {}, {}, elapsedTime }) });
					++createdRibbonsCount;
				}
			}
		}

		return createdRibbonsCount;
	}

	void RandomParticleConnector::updateRibbon(RibbonView& ribbon, const PathConfiguration& pathConfiguration, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle)
	{
		ribbon.points[0] = TrailPoint{ glm::vec4{}, fromParticle.postBehaviorPosition, 0.0f, 0.0f, ribbon.points[0].spawnTime };
		ribbon.points[1] = TrailPoint{ glm::vec4{}, toParticle.postBehaviorPosition, 0.0f, 1.0f, ribbon.points[1].spawnTime };

		float length = glm::distance(fromParticle.postBehaviorPosition, toParticle.postBehaviorPosition);

		for (unsigned int i = 0; i < ribbon.points.size(); ++i)
		{
			float t = static_cast<float>(i) / static_cast<float>(ribbon.points.size() - 1);
			ribbon.points[i].position = glm::mix(fromParticle.postBehaviorPosition, toParticle.postBehaviorPosition, t);
			ribbon.points[i].distanceOnTrail = length * t;
		}
	}

	bool RandomParticleConnector::isRibbonValid(const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const
	{
		glm::vec3 delta = fromParticle.postBehaviorPosition - toParticle.postBehaviorPosition;
		return glm::dot(delta, delta) <= m_maximumDistance;
	}
}