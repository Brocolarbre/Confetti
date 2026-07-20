#include "Confetti/Simulation/Core/ParticleSimulation.hpp"

namespace cft
{
	void ParticleSimulation::updateParticleEffects(float elapsedTime, float deltaTime)
	{
		for (unsigned int i = 0; i < m_particleEffectInstances.size();)
		{
			ParticleEffectInstance& particleEffectInstance = m_particleEffectInstances[i];

			for (unsigned int j = 0; j < particleEffectInstance.emitterSpawnContexts.size();)
			{
				const ParticleEmitterSpawnContext& emitterSpawnContext = particleEffectInstance.emitterSpawnContexts[j];
				if (elapsedTime >= particleEffectInstance.spawnTime + emitterSpawnContext.timeRange.spawnTime)
				{
					ParticleEmitterInstance particleEmitterInstance = createParticleEmitter(emitterSpawnContext, MotionState{}, 0, elapsedTime);

					m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, 1);

					if (particleEmitterInstance.trailRegistryId.has_value())
						m_trailRegistry.addReferenceCount(particleEmitterInstance.trailRegistryId.value(), 1);

					if (particleEmitterInstance.ribbonRegistryId.has_value())
						m_ribbonRegistry.addReferenceCount(particleEmitterInstance.ribbonRegistryId.value(), 1);

					m_particleEmitterInstances.push_back(std::move(particleEmitterInstance));

					particleEffectInstance.emitterSpawnContexts[j] = std::move(particleEffectInstance.emitterSpawnContexts.back());
					particleEffectInstance.emitterSpawnContexts.pop_back();
				}
				else
				{
					++j;
				}
			}

			if (particleEffectInstance.emitterSpawnContexts.empty())
			{
				m_particleEffectInstances[i] = std::move(m_particleEffectInstances.back());
				m_particleEffectInstances.pop_back();
			}
			else
			{
				++i;
			}
		}
	}
}