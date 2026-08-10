#include "Confetti/Simulation/Core/ParticleSimulation.hpp"
#include "Confetti/Simulation/Core/ParticleSimulationPath.hpp"

#include <execution>

namespace cft
{
	void ParticleSimulation::updateRibbons(float elapsedTime, float deltaTime)
	{
		for (auto& [ribbonRegistryId, ribbonRegistryEntry] : m_ribbonRegistry.getEntries())
		{
			if (m_particlePools[ribbonRegistryEntry.poolId].getCount() > 2)
			{
				unsigned int createdRibbonsCount = ribbonRegistryEntry.particleLinker->createRibbons(ribbonRegistryEntry.ribbonConfiguration.ribbonPointCount, m_ribbonPools[ribbonRegistryEntry.poolId], m_particlePools[ribbonRegistryEntry.poolId], ribbonRegistryId, elapsedTime);
				m_ribbonRegistry.addReferenceCount(ribbonRegistryId, createdRibbonsCount);
			}
		}

		std::vector<std::future<RibbonUpdateResult>> ribbonUpdateFutureResults;

		unsigned int totalRibbonCount = 0;
		for (auto& [poolId, pool] : m_ribbonPools)
			totalRibbonCount += pool.getCount();

		unsigned int desiredTasks = std::max(1u, static_cast<unsigned int>(m_threadPool.threadCount() * 2));
		unsigned int chunkSize = std::max(64u, (totalRibbonCount + desiredTasks - 1) / desiredTasks);

		for (auto& [poolId, ribbonPool] : m_ribbonPools)
		{
			unsigned int count = ribbonPool.getCount();

			for (unsigned int begin = 0; begin < count; begin += chunkSize)
			{
				unsigned int end = std::min(begin + chunkSize, count);

				ribbonUpdateFutureResults.push_back(m_threadPool.enqueue([&, poolId, begin, end]() {
					return updateRibbonBatch(poolId, ribbonPool, begin, end, elapsedTime, deltaTime);
				}));
			}
		}

		std::vector<RibbonUpdateResult> results;
		results.reserve(ribbonUpdateFutureResults.size());

		for (std::future<RibbonUpdateResult>& futureResult : ribbonUpdateFutureResults)
			results.push_back(futureResult.get());

		std::vector<RibbonRemoval> removals;

		for (RibbonUpdateResult& result : results)
			removals.insert(removals.end(), result.removedRibbons.begin(), result.removedRibbons.end());

		std::sort(std::execution::par_unseq, removals.begin(), removals.end(), [](auto& a, auto& b) {
			if (a.poolId != b.poolId)
				return a.poolId < b.poolId;

			return a.ribbonIndex > b.ribbonIndex;
		});

		for (RibbonRemoval& removal : removals)
		{
			m_ribbonRegistry.addReferenceCount(removal.ribbonRegistryId, -1);
			m_ribbonPools.at(removal.poolId).remove(removal.ribbonIndex);
		}
	}

	RibbonUpdateResult ParticleSimulation::updateRibbonBatch(unsigned int poolId, RibbonPool& ribbonPool, unsigned int begin, unsigned int end, float elapsedTime, float deltaTime)
	{
		RibbonUpdateResult result;

		const std::vector<unsigned int>& ribbonRegistryId = ribbonPool.getRibbonRegistryId();
		const std::vector<unsigned int>& fromParticleId = ribbonPool.getFromParticleId();
		const std::vector<unsigned int>& toParticleId = ribbonPool.getToParticleId();
		const std::vector<float>& spawnTime = ribbonPool.getSpawnTime();
		std::vector<std::deque<PathPoint>>& ribbonPoints = ribbonPool.getRibbonPoints();

		for (unsigned int i = begin; i < end; ++i)
		{
			RibbonRegistryEntry& ribbonRegistryEntry = m_ribbonRegistry.getEntry(ribbonRegistryId[i]);
			const ParticlePool& particlePool = m_particlePools[ribbonRegistryEntry.poolId];

			const std::vector<glm::vec4>& particleColor = particlePool.getColor();
			const std::vector<glm::vec3>& particlePosition = particlePool.getPosition();
			const std::vector<glm::quat>& particleRotation = particlePool.getRotation();
			const std::vector<glm::vec3>& particleScale = particlePool.getScale();
			const std::vector<glm::vec3>& particleLinearVelocity = particlePool.getLinearVelocity();
			const std::vector<glm::vec3>& particleAngularVelocity = particlePool.getAngularVelocity();
			const std::vector<glm::vec4>& particleInitialColor = particlePool.getInitialColor();
			const std::vector<glm::vec3>& particleInitialScale = particlePool.getInitialScale();
			const std::vector<glm::vec3>& particlePostBehaviorPosition = particlePool.getPostBehaviorPosition();
			const std::vector<float>& particlePhase = particlePool.getPhase();
			const std::vector<float>& particleLifetime = particlePool.getLifetime();
			const std::vector<float>& particleSpawnTime = particlePool.getSpawnTime();
			const std::vector<unsigned int>& particleId = particlePool.getId();
			const std::vector<unsigned int>& particleParticleRegistryId = particlePool.getParticleRegistryId();

			std::optional<unsigned int> fromParticleIndex = particlePool.getIndex(fromParticleId[i]);
			std::optional<unsigned int> toParticleIndex = particlePool.getIndex(toParticleId[i]);

			if (!fromParticleIndex.has_value() || !toParticleIndex.has_value() || (ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.lifetime.has_value() && (elapsedTime - spawnTime[i]) > ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.lifetime.value()))
			{
				result.removedRibbons.push_back(RibbonRemoval{ poolId, i, ribbonRegistryId[i] });
			}
			else
			{
				unsigned int fromParticleIndexValue = fromParticleIndex.value();
				unsigned int toParticleIndexValue = toParticleIndex.value();

				ConstantParticleView fromParticle{ particleColor[fromParticleIndexValue], particlePosition[fromParticleIndexValue], particleRotation[fromParticleIndexValue], particleScale[fromParticleIndexValue], particleLinearVelocity[fromParticleIndexValue], particleAngularVelocity[fromParticleIndexValue], particleInitialColor[fromParticleIndexValue], particleInitialScale[fromParticleIndexValue], particlePostBehaviorPosition[fromParticleIndexValue], particlePhase[fromParticleIndexValue], particleLifetime[fromParticleIndexValue], particleSpawnTime[fromParticleIndexValue], particleParticleRegistryId[fromParticleIndexValue], particleId[fromParticleIndexValue] };
				ConstantParticleView toParticle{ particleColor[toParticleIndexValue], particlePosition[toParticleIndexValue], particleRotation[toParticleIndexValue], particleScale[toParticleIndexValue], particleLinearVelocity[toParticleIndexValue], particleAngularVelocity[toParticleIndexValue], particleInitialColor[toParticleIndexValue], particleInitialScale[toParticleIndexValue], particlePostBehaviorPosition[toParticleIndexValue], particlePhase[toParticleIndexValue], particleLifetime[toParticleIndexValue], particleSpawnTime[toParticleIndexValue], particleParticleRegistryId[toParticleIndexValue], particleId[toParticleIndexValue] };

				if (ribbonRegistryEntry.particleLinker->isRibbonValid(LinkContext{ fromParticle, toParticle, ribbonPool, elapsedTime }))
				{
					unsigned int colorGradientSize = static_cast<unsigned int>(ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.colorGradient.size()) + (ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.appendParticleColor ? 2 : 0);
					std::vector<glm::vec4> colorGradient;
					colorGradient.reserve(colorGradientSize);
					if (ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.appendParticleColor)
						colorGradient.push_back(fromParticle.color);
					colorGradient.insert(colorGradient.end(), ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.colorGradient.begin(), ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.colorGradient.end());
					if (ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.appendParticleColor)
						colorGradient.push_back(toParticle.color);

					std::deque<PathPoint>& ribbon = ribbonPoints[i];

					if (ribbon.size() >= 2)
					{
						ribbon.front().position = fromParticle.postBehaviorPosition;
						ribbon.back().position = toParticle.postBehaviorPosition;
					}

					std::vector<glm::vec3> ribbonPointPositions = ribbonRegistryEntry.ribbonGenerator->generateRibbon(glm::max(static_cast<int>(ribbonRegistryEntry.ribbonConfiguration.ribbonPointCount) - 2, 0), elapsedTime, fromParticle, toParticle);

					float accumulatedDistance = 0.0f;
					glm::vec3 previousPointPosition = ribbon.front().position;
					for (unsigned int pathPointIndex = 1; pathPointIndex < ribbon.size() - 1; ++pathPointIndex)
					{
						ribbon[pathPointIndex].position = ribbonPointPositions[static_cast<size_t>(pathPointIndex) - 1];
						ribbon[pathPointIndex].distanceOnPath = glm::distance(previousPointPosition, ribbon[pathPointIndex].position);
					}

					ParticleSimulationPath::update(ribbon, ribbonRegistryEntry.ribbonConfiguration.pathConfiguration, colorGradient, elapsedTime);
				}
				else
				{
					result.removedRibbons.push_back(RibbonRemoval{ poolId, i, ribbonRegistryId[i] });
				}
			}
		}

		return result;
	}
}