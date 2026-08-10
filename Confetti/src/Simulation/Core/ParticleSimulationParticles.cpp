#include "Confetti/Simulation/Core/ParticleSimulation.hpp"

#include <glm/glm.hpp>
#include <execution>
#include <future>

namespace cft
{
	void ParticleSimulation::updateParticles(float elapsedTime, float deltaTime)
	{
		std::unordered_set<unsigned int> triggeredPeriodicSpawnTriggers;

		for (auto& [id, entry] : m_particleRegistry.getEntries())
		{
			if (entry.spawnTriggerDescriptor.has_value() && entry.spawnTriggerDescriptor.value().periodicEmitterSpawnContext.has_value())
			{
				SpawnTriggerDescriptor& spawnTriggerDescriptor = entry.spawnTriggerDescriptor.value();
				if (spawnTriggerDescriptor.periodicEmitterSpawnContext.has_value())
				{
					PeriodicSpawnTriggerContext& periodicSpawnTriggerContext = spawnTriggerDescriptor.periodicEmitterSpawnContext.value();
					entry.periodicTriggerAccumulator += deltaTime;

					if (entry.recursionDepth < spawnTriggerDescriptor.maximumRecursionDepth && entry.periodicTriggerAccumulator >= periodicSpawnTriggerContext.interval)
					{
						triggeredPeriodicSpawnTriggers.insert(id);
						entry.periodicTriggerAccumulator -= periodicSpawnTriggerContext.interval;
					}
				}
			}
		}

		std::vector<std::future<ParticleUpdateResult>> particleUpdateFutureResults;

		unsigned int totalParticleCount = 0;
		for (auto& [poolId, pool] : m_particlePools)
			totalParticleCount += pool.getCount();

		unsigned int desiredTasks = std::max(1u, static_cast<unsigned int>(m_threadPool.threadCount() * 4));
		unsigned int chunkSize = std::max(1024u, (totalParticleCount + desiredTasks - 1) / desiredTasks);

		for (auto& [poolId, pool] : m_particlePools)
		{
			unsigned int count = pool.getCount();

			for (unsigned int begin = 0; begin < count; begin += chunkSize)
			{
				unsigned int end = std::min(begin + chunkSize, count);

				particleUpdateFutureResults.push_back(m_threadPool.enqueue([&, poolId, begin, end]() {
					return updateParticleBatch(poolId, pool, begin, end, triggeredPeriodicSpawnTriggers, elapsedTime, deltaTime);
				}));
			}
		}

		std::vector<ParticleUpdateResult> results;
		results.reserve(particleUpdateFutureResults.size());
		
		for (std::future<ParticleUpdateResult>& futureResult : particleUpdateFutureResults)
			results.push_back(futureResult.get());

		std::vector<ParticleEmitterSpawnRequest> spawnRequests;
		std::vector<ParticleRemoval> removals;

		for (ParticleUpdateResult& result : results)
		{
			spawnRequests.insert(spawnRequests.end(), result.emitterSpawnRequests.begin(), result.emitterSpawnRequests.end());
			removals.insert(removals.end(), result.removedParticles.begin(), result.removedParticles.end());
		}

		std::sort(std::execution::par_unseq, spawnRequests.begin(), spawnRequests.end(), [](const auto& a, const auto& b) {
			return a.sourceParticleId < b.sourceParticleId;
		});

		for (ParticleEmitterSpawnRequest& spawnRequest : spawnRequests)
		{
			ParticleEmitterInstance emitter = createParticleEmitter(spawnRequest.spawnContext, spawnRequest.motionState, spawnRequest.parentSeed, spawnRequest.recursionDepth, elapsedTime);
			m_particleRegistry.addReferenceCount(emitter.particleRegistryId, 1);

			if (emitter.trailRegistryId.has_value())
				m_trailRegistry.addReferenceCount(emitter.trailRegistryId.value(), 1);

			if (emitter.ribbonRegistryId.has_value())
				m_ribbonRegistry.addReferenceCount(emitter.ribbonRegistryId.value(), 1);

			m_particleEmitterInstances.push_back(std::move(emitter));
		}	

		std::sort(std::execution::par_unseq, removals.begin(), removals.end(), [](const auto& a, const auto& b) {
			if (a.poolId != b.poolId)
				return a.poolId < b.poolId;

			return a.particleIndex > b.particleIndex;
		});

		for (ParticleRemoval& removal : removals)
		{
			m_particleRegistry.addReferenceCount(removal.particleRegistryId, -1);
			m_particlePools.at(removal.poolId).remove(removal.particleIndex);
		}
	}

	ParticleUpdateResult ParticleSimulation::updateParticleBatch(unsigned int poolId, ParticlePool& particlePool, unsigned int begin, unsigned int end, const std::unordered_set<unsigned int>& triggeredPeriodicSpawnTriggers, float elapsedTime, float deltaTime)
	{
		ParticleUpdateResult result;

		std::vector<glm::vec4>& color = particlePool.getColor();
		std::vector<glm::vec3>& position = particlePool.getPosition();
		std::vector<glm::quat>& rotation = particlePool.getRotation();
		std::vector<glm::vec3>& scale = particlePool.getScale();
		std::vector<glm::vec3>& linearVelocity = particlePool.getLinearVelocity();
		std::vector<glm::vec3>& angularVelocity = particlePool.getAngularVelocity();
		const std::vector<glm::vec4>& initialColor = particlePool.getInitialColor();
		const std::vector<glm::vec3>& initialScale = particlePool.getInitialScale();
		std::vector<glm::vec3>& postBehaviorPosition = particlePool.getPostBehaviorPosition();
		const std::vector<float>& phase = particlePool.getPhase();
		const std::vector<float>& lifetime = particlePool.getLifetime();
		const std::vector<float>& spawnTime = particlePool.getSpawnTime();
		const std::vector<unsigned int>& id = particlePool.getId();
		const std::vector<unsigned int>& particleRegistryId = particlePool.getParticleRegistryId();

		for (unsigned int i = begin; i < end; ++i)
		{
			ParticleRegistryEntry& entry = m_particleRegistry.getEntry(particleRegistryId[i]);

			float despawnTime = spawnTime[i] + lifetime[i];
			if (elapsedTime >= despawnTime)
			{
				if (entry.spawnTriggerDescriptor.has_value())
				{
					const auto& trigger = entry.spawnTriggerDescriptor.value();

					if (entry.recursionDepth < trigger.maximumRecursionDepth && trigger.deathEmitterSpawnContext.has_value())
						result.emitterSpawnRequests.push_back({ id[i], trigger.deathEmitterSpawnContext.value(), MotionState{position[i], linearVelocity[i], rotation[i], angularVelocity[i]}, entry.parentSeed, entry.recursionDepth + 1});
				}

				result.removedParticles.push_back({ poolId, i, particleRegistryId[i] });
			}
			else
			{
				if (triggeredPeriodicSpawnTriggers.find(particleRegistryId[i]) != triggeredPeriodicSpawnTriggers.end())
					result.emitterSpawnRequests.push_back({ id[i], entry.spawnTriggerDescriptor->periodicEmitterSpawnContext->emitterSpawnContext, MotionState{ position[i], linearVelocity[i], rotation[i], angularVelocity[i] }, entry.parentSeed, entry.recursionDepth + 1 });
				
				MotionState motionState{ position[i], linearVelocity[i], rotation[i], angularVelocity[i] };
				for (const std::unique_ptr<ForceField>& forceField : entry.forceFields)
				{
					MotionAcceleration motionAcceleration = forceField->evaluate(motionState);

					motionState.linearVelocity += motionAcceleration.linear * deltaTime;
					motionState.angularVelocity += motionAcceleration.angular * deltaTime;
				}

				motionState.position += motionState.linearVelocity * deltaTime;
				motionState.rotation = glm::normalize(glm::quat(1.0f, 0.5f * motionState.angularVelocity * deltaTime) * motionState.rotation);

				position[i] = motionState.position;
				rotation[i] = motionState.rotation;
				linearVelocity[i] = motionState.linearVelocity;
				angularVelocity[i] = motionState.angularVelocity;

				postBehaviorPosition[i] = motionState.position;

				float particleAge = elapsedTime - spawnTime[i];

				for (const std::unique_ptr<MotionBehavior>& motionBehavior : entry.motionBehaviors)
					postBehaviorPosition[i] += motionBehavior->evaluate(particleAge, motionState);

				float particleNormalizedAge = particleAge / lifetime[i];

				for (const std::unique_ptr<VisualBehavior>& visualBehavior : entry.visualBehaviors)
					visualBehavior->evaluate(elapsedTime, particleNormalizedAge, ParticleView{ color[i], position[i], rotation[i], scale[i], linearVelocity[i], angularVelocity[i], initialColor[i], initialScale[i], postBehaviorPosition[i], phase[i], lifetime[i], spawnTime[i], particleRegistryId[i], id[i] });
			}
		}

		return result;
	}
}