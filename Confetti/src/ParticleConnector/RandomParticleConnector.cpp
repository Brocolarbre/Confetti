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
					ribbonPool.insert(Ribbon{ ribbonRegistryId, particleId[randomIndexFrom], particleId[randomIndexTo], elapsedTime, {} });
					++createdRibbonsCount;
				}
			}
		}

		return createdRibbonsCount;
	}

	void RandomParticleConnector::updateRibbon(RibbonView& ribbon, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle)
	{
		if (ribbon.points.empty())
		{
			ribbon.points.push_back(TrailPoint{ fromParticle.color, fromParticle.position, 0.2f, 0.0f, 0.0f });
			ribbon.points.push_back(TrailPoint{ toParticle.color, toParticle.position, 0.2f, 1.0f, 0.0f });
		}
		else
		{
			ribbon.points[0] = TrailPoint{ fromParticle.color, fromParticle.position, 0.2f, 0.0f, 0.0f };
			ribbon.points[1] = TrailPoint{ toParticle.color, toParticle.position, 0.2f, 1.0f, 0.0f };
		}
	}

	bool RandomParticleConnector::isRibbonValid(const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const
	{
		glm::vec3 delta = fromParticle.postBehaviorPosition - toParticle.postBehaviorPosition;
		return glm::dot(delta, delta) <= m_maximumDistance;
	}
}