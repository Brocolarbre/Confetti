#include "Confetti/ParticleSimulation/ParticleRegistry.hpp"

namespace cft
{
	void ParticleRegistry::addForceField(unsigned int id, std::unique_ptr<ForceField> forceField)
	{
		m_forceFields[id] = std::move(forceField);
	}

	void ParticleRegistry::addParticleBehavior(unsigned int id, std::unique_ptr<ParticleBehavior> particleBehavior)
	{
		m_particleBehaviors[id] = std::move(particleBehavior);
	}

	void ParticleRegistry::addParticleEmitterBehavior(unsigned int id, std::unique_ptr<ParticleEmitterBehavior> particleEmitterBehavior)
	{
		m_particleEmitterBehaviors[id] = std::move(particleEmitterBehavior);
	}

	void ParticleRegistry::addParticleSpawner(unsigned int id, std::unique_ptr<ParticleSpawner> particleSpawner)
	{
		m_particleSpawners[id] = std::move(particleSpawner);
	}

	void ParticleRegistry::addSpawnPolicy(unsigned int id, std::unique_ptr<SpawnPolicy> spawnPolicy)
	{
		m_spawnPolicies[id] = std::move(spawnPolicy);
	}

	void ParticleRegistry::addParticleEffect(unsigned int id, const ParticleEffect& particleEffect)
	{
		m_particleEffects[id] = particleEffect;
	}

	void ParticleRegistry::addParticleEmitter(unsigned int id, const ParticleEmitter& particleEmitter)
	{
		m_particleEmitters[id] = particleEmitter;
	}

	void ParticleRegistry::removeForceField(unsigned int id)
	{
		m_forceFields.erase(id);
	}

	void ParticleRegistry::removeParticleBehavior(unsigned int id)
	{
		m_particleBehaviors.erase(id);
	}

	void ParticleRegistry::removeParticleEmitterBehavior(unsigned int id)
	{
		m_particleEmitterBehaviors.erase(id);
	}

	void ParticleRegistry::removeParticleSpawner(unsigned int id)
	{
		m_particleSpawners.erase(id);
	}

	void ParticleRegistry::removeSpawnPolicy(unsigned int id)
	{
		m_spawnPolicies.erase(id);
	}

	void ParticleRegistry::removeParticleEffect(unsigned int id)
	{
		m_particleEffects.erase(id);
	}

	void ParticleRegistry::removeParticleEmitter(unsigned int id)
	{
		m_particleEmitters.erase(id);
	}

	const ForceField& ParticleRegistry::getForceField(unsigned int id) const
	{
		return *m_forceFields.at(id);
	}

	const ParticleBehavior& ParticleRegistry::getParticleBehavior(unsigned int id) const
	{
		return *m_particleBehaviors.at(id);
	}

	const ParticleEmitterBehavior& ParticleRegistry::getParticleEmitterBehavior(unsigned int id) const
	{
		return *m_particleEmitterBehaviors.at(id);
	}

	const ParticleSpawner& ParticleRegistry::getParticleSpawner(unsigned int id) const
	{
		return *m_particleSpawners.at(id);
	}

	const SpawnPolicy& ParticleRegistry::getSpawnPolicy(unsigned int id) const
	{
		return *m_spawnPolicies.at(id);
	}

	const ParticleEffect& ParticleRegistry::getParticleEffect(unsigned int id) const
	{
		return m_particleEffects.at(id);
	}

	const ParticleEmitter& ParticleRegistry::getParticleEmitter(unsigned int id) const
	{
		return m_particleEmitters.at(id);
	}

	ForceField& ParticleRegistry::getForceField(unsigned int id)
	{
		return *m_forceFields.at(id);
	}

	ParticleBehavior& ParticleRegistry::getParticleBehavior(unsigned int id)
	{
		return *m_particleBehaviors.at(id);
	}

	ParticleEmitterBehavior& ParticleRegistry::getParticleEmitterBehavior(unsigned int id)
	{
		return *m_particleEmitterBehaviors.at(id);
	}

	ParticleSpawner& ParticleRegistry::getParticleSpawner(unsigned int id)
	{
		return *m_particleSpawners.at(id);
	}

	SpawnPolicy& ParticleRegistry::getSpawnPolicy(unsigned int id)
	{
		return *m_spawnPolicies.at(id);
	}

	ParticleEffect& ParticleRegistry::getParticleEffect(unsigned int id)
	{
		return m_particleEffects.at(id);
	}

	ParticleEmitter& ParticleRegistry::getParticleEmitter(unsigned int id)
	{
		return m_particleEmitters.at(id);
	}
}