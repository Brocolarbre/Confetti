#include "Confetti/Simulation/Core/ParticleSimulation.hpp"
#include "Confetti/Simulation/Core/ParticleSimulationPath.hpp"

#include <execution>

namespace cft
{
	void ParticleSimulation::updateTrails(float elapsedTime, float deltaTime)
	{
		std::vector<std::future<TrailUpdateResult>> trailUpdateFutureResults;

		unsigned int totalTrailCount = 0;
		for (auto& [poolId, pool] : m_trailPools)
			totalTrailCount += pool.getCount();

		unsigned int desiredTasks = std::max(1u, static_cast<unsigned int>(m_threadPool.threadCount() * 2));
		unsigned int chunkSize = std::max(128u, (totalTrailCount + desiredTasks - 1) / desiredTasks);

		for (auto& [poolId, trailPool] : m_trailPools)
		{
			unsigned int count = trailPool.getCount();

			for (unsigned int begin = 0; begin < count; begin += chunkSize)
			{
				unsigned int end = std::min(begin + chunkSize, count);

				trailUpdateFutureResults.push_back(m_threadPool.enqueue([&, poolId, begin, end]() {
					return updateTrailBatch(poolId, trailPool, begin, end, elapsedTime, deltaTime);
				}));
			}
		}

		std::vector<TrailUpdateResult> results;
		results.reserve(trailUpdateFutureResults.size());

		for (std::future<TrailUpdateResult>& futureResult : trailUpdateFutureResults)
			results.push_back(futureResult.get());

		std::vector<TrailRemoval> removals;

		for (TrailUpdateResult& result : results)
			removals.insert(removals.end(), result.removedTrails.begin(), result.removedTrails.end());

		std::sort(std::execution::par_unseq, removals.begin(), removals.end(), [](auto& a, auto& b) {
			if (a.poolId != b.poolId)
				return a.poolId < b.poolId;

			return a.trailIndex > b.trailIndex;
		});

		for (TrailRemoval& removal : removals)
		{
			m_trailRegistry.addReferenceCount(removal.trailRegistryId, -1);
			m_trailPools.at(removal.poolId).remove(removal.trailIndex);
		}
	}

	TrailUpdateResult ParticleSimulation::updateTrailBatch(unsigned int poolId, TrailPool& trailPool, unsigned int begin, unsigned int end, float elapsedTime, float deltaTime)
	{
		TrailUpdateResult result;

		const std::vector<unsigned int>& trailRegistryId = trailPool.getTrailRegistryId();
		const std::vector<unsigned int>& particleId = trailPool.getParticleId();
		std::vector<float>& particleDeathTime = trailPool.getParticleDeathTime();
		std::vector<glm::vec4>& particleColor = trailPool.getParticleColor();
		std::vector<std::deque<PathPoint>>& trailPoints = trailPool.getPathPoints();

		for (unsigned int i = begin; i < end; ++i)
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
							distanceOnTrail = trailPoints[i].back().distanceOnPath + glm::distance(trailPoints[i].back().position, particlePosition);

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
				result.removedTrails.push_back(TrailRemoval{ poolId, i, trailRegistryId[i] });
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
			}
		}

		return result;
	}
}