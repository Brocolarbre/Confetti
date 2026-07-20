#include "Confetti/Simulation/Core/ParticleSimulation.hpp"

namespace cft
{
	void ParticleSimulation::updateParticleEmitters(float elapsedTime, float deltaTime)
	{
		std::vector<ParticleEmitterInstance> pendingParticleEmitterInstances;

		for (unsigned int i = 0; i < m_particleEmitterInstances.size();)
		{
			ParticleEmitterInstance& particleEmitterInstance = m_particleEmitterInstances[i];

			float despawnTime = particleEmitterInstance.timeRange.spawnTime + particleEmitterInstance.timeRange.duration;
			if (elapsedTime >= despawnTime)
			{
				m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, -1);

				if (particleEmitterInstance.trailRegistryId.has_value())
					m_trailRegistry.addReferenceCount(particleEmitterInstance.trailRegistryId.value(), -1);

				if (particleEmitterInstance.ribbonRegistryId.has_value())
					m_ribbonRegistry.addReferenceCount(particleEmitterInstance.ribbonRegistryId.value(), -1);

				m_particleEmitterInstances[i] = std::move(m_particleEmitterInstances.back());
				m_particleEmitterInstances.pop_back();
			}
			else
			{
				for (const std::unique_ptr<ForceField>& forceField : particleEmitterInstance.inheritedForceFields)
				{
					MotionAcceleration motionAcceleration = forceField->evaluate(particleEmitterInstance.motionState);

					particleEmitterInstance.motionState.linearVelocity += motionAcceleration.linear * deltaTime;
					particleEmitterInstance.motionState.angularVelocity += motionAcceleration.angular * deltaTime;
				}

				particleEmitterInstance.motionState.position += particleEmitterInstance.motionState.linearVelocity * deltaTime;
				particleEmitterInstance.motionState.rotation = glm::normalize(glm::quat(1.0f, 0.5f * particleEmitterInstance.motionState.angularVelocity * deltaTime) * particleEmitterInstance.motionState.rotation);

				particleEmitterInstance.postBehaviorPosition = particleEmitterInstance.motionState.position;

				for (const std::unique_ptr<MotionBehavior>& motionBehavior : particleEmitterInstance.inheritedMotionBehaviors)
					particleEmitterInstance.postBehaviorPosition += motionBehavior->evaluate(elapsedTime - particleEmitterInstance.timeRange.spawnTime, particleEmitterInstance.motionState);

				unsigned int particleSpawnCount = particleEmitterInstance.emissionPattern->emit(deltaTime);
				if (particleSpawnCount > 0)
				{
					std::vector<Particle> particles = particleEmitterInstance.particleSpawner->spawn(particleSpawnCount, elapsedTime, deltaTime, particleEmitterInstance.particleRegistryId);

					const ParticleRegistryEntry& particleRegistryEntry = m_particleRegistry.getEntry(particleEmitterInstance.particleRegistryId);
					ParticlePool& particlePool = m_particlePools.at(particleRegistryEntry.poolId);
					particlePool.reserve(particleSpawnCount);

					bool spawnSpawnTrigger = false;
					ParticleEmitterSpawnContext spawnParticleEmitterSpawnContext;
					if (particleRegistryEntry.spawnTriggerDescriptor.has_value())
					{
						const SpawnTriggerDescriptor& spawnTriggerDescriptorValue = particleRegistryEntry.spawnTriggerDescriptor.value();
						spawnSpawnTrigger = particleRegistryEntry.recursionDepth < spawnTriggerDescriptorValue.maximumRecursionDepth && spawnTriggerDescriptorValue.spawnEmitterSpawnContext.has_value();
						if (spawnSpawnTrigger)
							spawnParticleEmitterSpawnContext = spawnTriggerDescriptorValue.spawnEmitterSpawnContext.value();
					}

					bool spawnTrails = particleEmitterInstance.trailRegistryId.has_value();
					std::optional<TrailPool*> trailPool;
					if (spawnTrails)
					{
						trailPool = &m_trailPools.at(particleRegistryEntry.poolId);
						trailPool.value()->reserve(particleSpawnCount);
					}

					for (Particle& particle : particles)
					{
						particle.position += particleEmitterInstance.postBehaviorPosition;
						particle.linearVelocity += particleEmitterInstance.motionState.linearVelocity;
						particlePool.insert(particle);

						if (spawnTrails)
							trailPool.value()->insert(Trail{ particleEmitterInstance.trailRegistryId.value(), particle.id, -1.0f, particle.color, {} });

						if (spawnSpawnTrigger)
						{
							ParticleEmitterInstance spawnParticleEmitterInstance = createParticleEmitter(spawnParticleEmitterSpawnContext, MotionState{ particle.position, particle.linearVelocity, particle.rotation, particle.angularVelocity }, particleRegistryEntry.recursionDepth + 1, elapsedTime);
							pendingParticleEmitterInstances.push_back(std::move(spawnParticleEmitterInstance));
						}
					}

					m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, particleSpawnCount);
					if (spawnTrails)
						m_trailRegistry.addReferenceCount(particleEmitterInstance.trailRegistryId.value(), particleSpawnCount);
				}

				++i;
			}
		}

		for (ParticleEmitterInstance& particleEmitterInstance : pendingParticleEmitterInstances)
		{
			m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, 1);
			if (particleEmitterInstance.trailRegistryId.has_value())
				m_trailRegistry.addReferenceCount(particleEmitterInstance.trailRegistryId.value(), 1);

			m_particleEmitterInstances.push_back(std::move(particleEmitterInstance));
		}
	}
}