#include "Confetti/Simulation/Core/ParticleSimulation.hpp"

#include <glm/glm.hpp>

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

		for (auto& [poolId, particlePool] : m_particlePools)
		{
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

			std::unordered_map<unsigned int, unsigned int> removedParticleCount;

			for (unsigned int i = 0; i < particlePool.getCount();)
			{
				ParticleRegistryEntry& entry = m_particleRegistry.getEntry(particleRegistryId[i]);

				float despawnTime = spawnTime[i] + lifetime[i];
				if (elapsedTime >= despawnTime)
				{
					if (entry.spawnTriggerDescriptor.has_value())
					{
						const SpawnTriggerDescriptor& spawnTriggerValue = entry.spawnTriggerDescriptor.value();
						if (entry.recursionDepth < spawnTriggerValue.maximumRecursionDepth && spawnTriggerValue.deathEmitterSpawnContext.has_value())
						{
							ParticleEmitterInstance deathParticleEmitterInstance = createParticleEmitter(spawnTriggerValue.deathEmitterSpawnContext.value(), MotionState{ position[i], linearVelocity[i], rotation[i], angularVelocity[i] }, entry.recursionDepth + 1, elapsedTime);
							m_particleRegistry.addReferenceCount(deathParticleEmitterInstance.particleRegistryId, 1);
							if (deathParticleEmitterInstance.trailRegistryId.has_value())
								m_trailRegistry.addReferenceCount(deathParticleEmitterInstance.trailRegistryId.value(), 1);
							m_particleEmitterInstances.push_back(std::move(deathParticleEmitterInstance));
						}
					}

					++removedParticleCount[particleRegistryId[i]];
					particlePool.remove(i);
				}
				else
				{
					if (triggeredPeriodicSpawnTriggers.find(particleRegistryId[i]) != triggeredPeriodicSpawnTriggers.end())
					{
						ParticleEmitterInstance periodicParticleEmitterInstance = createParticleEmitter(entry.spawnTriggerDescriptor.value().periodicEmitterSpawnContext.value().emitterSpawnContext, MotionState{ position[i], linearVelocity[i], rotation[i], angularVelocity[i] }, entry.recursionDepth + 1, elapsedTime);
						m_particleRegistry.addReferenceCount(periodicParticleEmitterInstance.particleRegistryId, 1);
						if (periodicParticleEmitterInstance.trailRegistryId.has_value())
							m_trailRegistry.addReferenceCount(periodicParticleEmitterInstance.trailRegistryId.value(), 1);
						m_particleEmitterInstances.push_back(std::move(periodicParticleEmitterInstance));
					}

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

					++i;
				}
			}

			for (auto& [particleRegistry, count] : removedParticleCount)
				m_particleRegistry.addReferenceCount(particleRegistry, -static_cast<int>(count));
		}
	}
}