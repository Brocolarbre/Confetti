#include "Confetti/ParticleSimulation/AssetRegistry.hpp"

namespace cft
{
	void AssetRegistry::addForceField(unsigned int id, std::unique_ptr<ForceField> forceField)
	{
		m_forceFields[id] = std::move(forceField);
	}

	void AssetRegistry::addMotionBehavior(unsigned int id, std::unique_ptr<MotionBehavior> motionBehavior)
	{
		m_motionBehaviors[id] = std::move(motionBehavior);
	}

	void AssetRegistry::addParticleBehavior(unsigned int id, std::unique_ptr<ParticleBehavior> particleBehavior)
	{
		m_particleBehaviors[id] = std::move(particleBehavior);
	}

	void AssetRegistry::addParticleSpawner(unsigned int id, std::unique_ptr<ParticleSpawner> particleSpawner)
	{
		m_particleSpawners[id] = std::move(particleSpawner);
	}

	void AssetRegistry::addSpawnPolicy(unsigned int id, std::unique_ptr<SpawnPolicy> spawnPolicy)
	{
		m_spawnPolicies[id] = std::move(spawnPolicy);
	}

	void AssetRegistry::addParticleEffect(unsigned int id, const ParticleEffect& particleEffect)
	{
		m_particleEffects[id] = particleEffect;
	}

	void AssetRegistry::addParticleEmitter(unsigned int id, const ParticleEmitter& particleEmitter)
	{
		m_particleEmitters[id] = particleEmitter;
	}

	void AssetRegistry::removeForceField(unsigned int id)
	{
		m_forceFields.erase(id);
	}

	void AssetRegistry::removeMotionBehavior(unsigned int id)
	{
		m_motionBehaviors.erase(id);
	}

	void AssetRegistry::removeParticleBehavior(unsigned int id)
	{
		m_particleBehaviors.erase(id);
	}

	void AssetRegistry::removeParticleSpawner(unsigned int id)
	{
		m_particleSpawners.erase(id);
	}

	void AssetRegistry::removeSpawnPolicy(unsigned int id)
	{
		m_spawnPolicies.erase(id);
	}

	void AssetRegistry::removeParticleEffect(unsigned int id)
	{
		m_particleEffects.erase(id);
	}

	void AssetRegistry::removeParticleEmitter(unsigned int id)
	{
		m_particleEmitters.erase(id);
	}

	const ForceField& AssetRegistry::getForceField(unsigned int id) const
	{
		return *m_forceFields.at(id);
	}

	const MotionBehavior& AssetRegistry::getMotionBehavior(unsigned int id) const
	{
		return *m_motionBehaviors.at(id);
	}

	const ParticleBehavior& AssetRegistry::getParticleBehavior(unsigned int id) const
	{
		return *m_particleBehaviors.at(id);
	}

	const ParticleSpawner& AssetRegistry::getParticleSpawner(unsigned int id) const
	{
		return *m_particleSpawners.at(id);
	}

	const SpawnPolicy& AssetRegistry::getSpawnPolicy(unsigned int id) const
	{
		return *m_spawnPolicies.at(id);
	}

	const ParticleEffect& AssetRegistry::getParticleEffect(unsigned int id) const
	{
		return m_particleEffects.at(id);
	}

	const ParticleEmitter& AssetRegistry::getParticleEmitter(unsigned int id) const
	{
		return m_particleEmitters.at(id);
	}

	ForceField& AssetRegistry::getForceField(unsigned int id)
	{
		return *m_forceFields.at(id);
	}

	MotionBehavior& AssetRegistry::getMotionBehavior(unsigned int id)
	{
		return *m_motionBehaviors.at(id);
	}

	ParticleBehavior& AssetRegistry::getParticleBehavior(unsigned int id)
	{
		return *m_particleBehaviors.at(id);
	}

	ParticleSpawner& AssetRegistry::getParticleSpawner(unsigned int id)
	{
		return *m_particleSpawners.at(id);
	}

	SpawnPolicy& AssetRegistry::getSpawnPolicy(unsigned int id)
	{
		return *m_spawnPolicies.at(id);
	}

	ParticleEffect& AssetRegistry::getParticleEffect(unsigned int id)
	{
		return m_particleEffects.at(id);
	}

	ParticleEmitter& AssetRegistry::getParticleEmitter(unsigned int id)
	{
		return m_particleEmitters.at(id);
	}
}