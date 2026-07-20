#include "Confetti/Simulation/Core/ParticleSimulation.hpp"
#include "Confetti/Simulation/Core/ParticleSimulationPath.hpp"

namespace cft
{
	void ParticleSimulation::updateTrails(float elapsedTime, float deltaTime)
	{
		for (auto& [poolId, trailPool] : m_trailPools)
		{
			const std::vector<unsigned int>& trailRegistryId = trailPool.getTrailRegistryId();
			const std::vector<unsigned int>& particleId = trailPool.getParticleId();
			std::vector<float>& particleDeathTime = trailPool.getParticleDeathTime();
			std::vector<glm::vec4>& particleColor = trailPool.getParticleColor();
			std::vector<std::deque<PathPoint>>& trailPoints = trailPool.getPathPoints();

			std::unordered_map<unsigned int, unsigned int> removedTrailCount;

			for (unsigned int i = 0; i < trailPool.getCount();)
			{
				TrailRegistryEntry& trailRegistryEntry = m_trailRegistry.getEntry(trailRegistryId[i]);

				if (particleDeathTime[i] < 0.0f)
				{
					const ParticlePool& particlePool = m_particlePools.at(poolId);

					std::optional<unsigned int> ownerParticleIndex = particlePool.getIndex(particleId[i]);
					if (!ownerParticleIndex.has_value())
					{
						particleDeathTime[i] = elapsedTime;
					}
					else
					{
						particleColor[i] = particlePool.getColor()[ownerParticleIndex.value()];
						glm::vec3 particlePosition = particlePool.getPostBehaviorPosition()[ownerParticleIndex.value()];
						if (trailPoints[i].empty() || glm::distance(particlePosition, trailPoints[i].back().position) > trailRegistryEntry.trailConfiguration.minimumSpawnDistance || (trailRegistryEntry.trailConfiguration.maximumSpawnTime.has_value() && elapsedTime - trailPoints[i].back().spawnTime > trailRegistryEntry.trailConfiguration.maximumSpawnTime.value()))
						{
							float distanceOnTrail = 0.0f;
							if (!trailPoints[i].empty())
								distanceOnTrail = trailPoints[i].back().distanceOnTrail + glm::distance(trailPoints[i].back().position, particlePosition);

							trailPoints[i].push_back(PathPoint{ glm::vec4(1.0f), particlePosition, 1.0f, distanceOnTrail, elapsedTime });

							if (trailRegistryEntry.trailConfiguration.maximumSegmentCount.has_value() && trailPoints[i].size() > trailRegistryEntry.trailConfiguration.maximumSegmentCount.value())
							{
								while (trailPoints[i].size() > trailRegistryEntry.trailConfiguration.maximumSegmentCount.value())
									trailPoints[i].pop_front();
							}
						}
					}
				}

				if (particleDeathTime[i] >= 0.0f && elapsedTime >= trailRegistryEntry.trailConfiguration.presistenceLifetime + particleDeathTime[i])
				{
					++removedTrailCount[trailRegistryId[i]];
					trailPool.remove(i);
				}
				else
				{
					unsigned int colorGradientSize = static_cast<unsigned int>(trailRegistryEntry.trailConfiguration.pathConfiguration.colorGradient.size()) + (trailRegistryEntry.trailConfiguration.pathConfiguration.appendParticleColor ? 1 : 0);
					std::vector<glm::vec4> colorGradient;
					colorGradient.reserve(colorGradientSize);
					if (trailRegistryEntry.trailConfiguration.pathConfiguration.appendParticleColor)
						colorGradient.push_back(particleColor[i]);
					colorGradient.insert(colorGradient.end(), trailRegistryEntry.trailConfiguration.pathConfiguration.colorGradient.begin(), trailRegistryEntry.trailConfiguration.pathConfiguration.colorGradient.end());

					ParticleSimulationPath::update(trailPoints[i], trailRegistryEntry.trailConfiguration.pathConfiguration, colorGradient, elapsedTime);

					++i;
				}
			}

			for (auto& [trailRegistry, count] : removedTrailCount)
				m_trailRegistry.addReferenceCount(trailRegistry, -static_cast<int>(count));
		}
	}
}