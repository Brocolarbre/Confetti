#include "Confetti/ParticleSimulation/AssetRegistry.hpp"

namespace cft
{
	void AssetRegistry::addImage(unsigned int id, std::unique_ptr<Image> image)
	{
		m_images[id] = std::move(image);
	}

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

	void AssetRegistry::removeImage(unsigned int id)
	{
		m_images.erase(id);
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

	const Image& AssetRegistry::getImage(unsigned int id) const
	{
		return *m_images.at(id);
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

	Image& AssetRegistry::getImage(unsigned int id)
	{
		return *m_images.at(id);
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

	const std::unordered_map<unsigned int, std::unique_ptr<Image>>& AssetRegistry::getImages() const
	{
		return m_images;
	}

	const std::unordered_map<unsigned int, std::unique_ptr<ForceField>>& AssetRegistry::getForceFields() const
	{
		return m_forceFields;
	}

	const std::unordered_map<unsigned int, std::unique_ptr<MotionBehavior>>& AssetRegistry::getMotionBehaviors() const
	{
		return m_motionBehaviors;
	}

	const std::unordered_map<unsigned int, std::unique_ptr<ParticleBehavior>>& AssetRegistry::getParticleBehaviors() const
	{
		return m_particleBehaviors;
	}

	const std::unordered_map<unsigned int, std::unique_ptr<ParticleSpawner>>& AssetRegistry::getParticleSpawners() const
	{
		return m_particleSpawners;
	}

	const std::unordered_map<unsigned int, std::unique_ptr<SpawnPolicy>>& AssetRegistry::getSpawnPolicies() const
	{
		return m_spawnPolicies;
	}

	const std::unordered_map<unsigned int, ParticleEffect>& AssetRegistry::getParticleEffects() const
	{
		return m_particleEffects;
	}

	const std::unordered_map<unsigned int, ParticleEmitter>& AssetRegistry::getParticleEmitters() const
	{
		return m_particleEmitters;
	}
}