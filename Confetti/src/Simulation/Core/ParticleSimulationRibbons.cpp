#include "Confetti/Simulation/Core/ParticleSimulation.hpp"
#include "Confetti/Simulation/Core/ParticleSimulationPath.hpp"

namespace cft
{
	void ParticleSimulation::updateRibbons(float elapsedTime, float deltaTime)
	{
		for (auto& [ribbonRegistryId, ribbonRegistryEntry] : m_ribbonRegistry.getEntries())
		{
			unsigned int createdRibbonsCount = ribbonRegistryEntry.particleLinker->createRibbons(ribbonRegistryEntry.ribbonConfiguration.ribbonPointCount, m_ribbonPools[ribbonRegistryEntry.poolId], m_particlePools[ribbonRegistryEntry.poolId], ribbonRegistryId, elapsedTime);
			m_ribbonRegistry.addReferenceCount(ribbonRegistryId, createdRibbonsCount);
		}

		for (auto& [poolId, ribbonPool] : m_ribbonPools)
		{
			const std::vector<unsigned int>& ribbonRegistryId = ribbonPool.getRibbonRegistryId();
			const std::vector<unsigned int>& fromParticleId = ribbonPool.getFromParticleId();
			const std::vector<unsigned int>& toParticleId = ribbonPool.getToParticleId();
			const std::vector<float>& spawnTime = ribbonPool.getSpawnTime();
			std::vector<std::deque<PathPoint>>& ribbonPoints = ribbonPool.getRibbonPoints();

			std::unordered_map<unsigned int, unsigned int> removedRibbonCount;

			for (unsigned int i = 0; i < ribbonPool.getCount();)
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
					ribbonPool.remove(i);
					++removedRibbonCount[ribbonRegistryId[i]];
				}
				else
				{
					unsigned int fromParticleIndexValue = fromParticleIndex.value();
					unsigned int toParticleIndexValue = toParticleIndex.value();

					ConstantParticleView fromParticle{ particleColor[fromParticleIndexValue], particlePosition[fromParticleIndexValue], particleRotation[fromParticleIndexValue], particleScale[fromParticleIndexValue], particleLinearVelocity[fromParticleIndexValue], particleAngularVelocity[fromParticleIndexValue], particleInitialColor[fromParticleIndexValue], particleInitialScale[fromParticleIndexValue], particlePostBehaviorPosition[fromParticleIndexValue], particlePhase[fromParticleIndexValue], particleLifetime[fromParticleIndexValue], particleSpawnTime[fromParticleIndexValue], particleParticleRegistryId[fromParticleIndexValue], particleId[fromParticleIndexValue] };
					ConstantParticleView toParticle{ particleColor[toParticleIndexValue], particlePosition[toParticleIndexValue], particleRotation[toParticleIndexValue], particleScale[toParticleIndexValue], particleLinearVelocity[toParticleIndexValue], particleAngularVelocity[toParticleIndexValue], particleInitialColor[toParticleIndexValue], particleInitialScale[toParticleIndexValue], particlePostBehaviorPosition[toParticleIndexValue], particlePhase[toParticleIndexValue], particleLifetime[toParticleIndexValue], particleSpawnTime[toParticleIndexValue], particleParticleRegistryId[toParticleIndexValue], particleId[toParticleIndexValue] };

					if (ribbonRegistryEntry.particleLinker->isRibbonValid(LinkContext{ fromParticle, toParticle, ribbonPool }))
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

						std::vector<glm::vec3> ribbonPointPositions = ribbonRegistryEntry.ribbonGenerator->generateRibbon(glm::max(static_cast<int>(ribbonRegistryEntry.ribbonConfiguration.ribbonPointCount) - 2, 0), fromParticle, toParticle);

						float accumulatedDistance = 0.0f;
						glm::vec3 previousPointPosition = ribbon.front().position;
						for (unsigned int pathPointIndex = 1; pathPointIndex < ribbon.size() - 1; ++pathPointIndex)
						{
							ribbon[pathPointIndex].position = ribbonPointPositions[static_cast<size_t>(pathPointIndex) - 1];
							ribbon[pathPointIndex].distanceOnPath = glm::distance(previousPointPosition, ribbon[pathPointIndex].position);
						}
						
						ParticleSimulationPath::update(ribbon, ribbonRegistryEntry.ribbonConfiguration.pathConfiguration, colorGradient, elapsedTime);

						++i;
					}
					else
					{
						ribbonPool.remove(i);
						++removedRibbonCount[ribbonRegistryId[i]];
					}
				}
			}

			for (auto& [ribbonRegistry, count] : removedRibbonCount)
				m_ribbonRegistry.addReferenceCount(ribbonRegistry, -static_cast<int>(count));
		}
	}
}