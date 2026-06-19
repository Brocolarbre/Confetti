#pragma once

#include "Confetti/ForceField/ForceField.hpp"
#include "Confetti/MotionBehavior/MotionBehavior.hpp"
#include "Confetti/Particle/Image.hpp"
#include "Confetti/Particle/Model.hpp"
#include "Confetti/Particle/ParticleEffect.hpp"
#include "Confetti/Particle/ParticleEmitter.hpp"
#include "Confetti/Particle/SpriteSheet.hpp"
#include "Confetti/ParticleBehavior/ParticleBehavior.hpp"
#include "Confetti/ParticleSpawner/ParticleSpawner.hpp"
#include "Confetti/SpawnPolicy/SpawnPolicy.hpp"

#include <unordered_map>

namespace cft
{
	class AssetRegistry
	{
	private:
		std::unordered_map<unsigned int, std::unique_ptr<ForceField>> m_forceFields;
		std::unordered_map<unsigned int, std::unique_ptr<MotionBehavior>> m_motionBehaviors;
		std::unordered_map<unsigned int, std::unique_ptr<ParticleBehavior>> m_particleBehaviors;
		std::unordered_map<unsigned int, std::unique_ptr<ParticleSpawner>> m_particleSpawners;
		std::unordered_map<unsigned int, std::unique_ptr<SpawnPolicy>> m_spawnPolicies;
		std::unordered_map<unsigned int, Image> m_images;
		std::unordered_map<unsigned int, Model> m_models;
		std::unordered_map<unsigned int, SpriteSheet> m_spriteSheets;
		std::unordered_map<unsigned int, ParticleEffect> m_particleEffects;
		std::unordered_map<unsigned int, ParticleEmitter> m_particleEmitters;

	public:
		void addForceField(unsigned int id, std::unique_ptr<ForceField> forceField);
		void addMotionBehavior(unsigned int id, std::unique_ptr<MotionBehavior> motionBehavior);
		void addParticleBehavior(unsigned int id, std::unique_ptr<ParticleBehavior> particleBehavior);
		void addParticleSpawner(unsigned int id, std::unique_ptr<ParticleSpawner> particleSpawner);
		void addSpawnPolicy(unsigned int id, std::unique_ptr<SpawnPolicy> spawnPolicy);
		void addImage(unsigned int id, Image image);
		void addModel(unsigned int id, Model model);
		void addSpriteSheet(unsigned int id, SpriteSheet spriteSheet);
		void addParticleEffect(unsigned int id, ParticleEffect particleEffect);
		void addParticleEmitter(unsigned int id, ParticleEmitter particleEmitter);

		void removeForceField(unsigned int id);
		void removeMotionBehavior(unsigned int id);
		void removeParticleBehavior(unsigned int id);
		void removeParticleSpawner(unsigned int id);
		void removeSpawnPolicy(unsigned int id);
		void removeImage(unsigned int id);
		void removeModel(unsigned int id);
		void removeSpriteSheet(unsigned int id);
		void removeParticleEffect(unsigned int id);
		void removeParticleEmitter(unsigned int id);

		const ForceField& getForceField(unsigned int id) const;
		const MotionBehavior& getMotionBehavior(unsigned int id) const;
		const ParticleBehavior& getParticleBehavior(unsigned int id) const;
		const ParticleSpawner& getParticleSpawner(unsigned int id) const;
		const SpawnPolicy& getSpawnPolicy(unsigned int id) const;
		const Image& getImage(unsigned int id) const;
		const Model& getModel(unsigned int id) const;
		const SpriteSheet& getSpriteSheet(unsigned int id) const;
		const ParticleEffect& getParticleEffect(unsigned int id) const;
		const ParticleEmitter& getParticleEmitter(unsigned int id) const;

		ForceField& getForceField(unsigned int id);
		MotionBehavior& getMotionBehavior(unsigned int id);
		ParticleBehavior& getParticleBehavior(unsigned int id);
		ParticleSpawner& getParticleSpawner(unsigned int id);
		SpawnPolicy& getSpawnPolicy(unsigned int id);
		Image& getImage(unsigned int id);
		Model& getModel(unsigned int id);
		SpriteSheet& getSpriteSheet(unsigned int id);
		ParticleEffect& getParticleEffect(unsigned int id);
		ParticleEmitter& getParticleEmitter(unsigned int id);

		const std::unordered_map<unsigned int, std::unique_ptr<ForceField>>& getForceFields() const;
		const std::unordered_map<unsigned int, std::unique_ptr<MotionBehavior>>& getMotionBehaviors() const;
		const std::unordered_map<unsigned int, std::unique_ptr<ParticleBehavior>>& getParticleBehaviors() const;
		const std::unordered_map<unsigned int, std::unique_ptr<ParticleSpawner>>& getParticleSpawners() const;
		const std::unordered_map<unsigned int, std::unique_ptr<SpawnPolicy>>& getSpawnPolicies() const;
		const std::unordered_map<unsigned int, Image>& getImages() const;
		const std::unordered_map<unsigned int, Model>& getModels() const;
		const std::unordered_map<unsigned int, SpriteSheet>& getSpriteSheets() const;
		const std::unordered_map<unsigned int, ParticleEffect>& getParticleEffects() const;
		const std::unordered_map<unsigned int, ParticleEmitter>& getParticleEmitters() const;
	};
}