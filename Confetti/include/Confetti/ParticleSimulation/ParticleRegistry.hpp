#pragma once

#include "Confetti/ForceField/ForceField.hpp"
#include "Confetti/Particle/ParticleEffect.hpp"
#include "Confetti/Particle/ParticleEmitter.hpp"
#include "Confetti/ParticleBehavior/ParticleBehavior.hpp"
#include "Confetti/ParticleEmitterBehavior/ParticleEmitterBehavior.hpp"
#include "Confetti/ParticleSpawner/ParticleSpawner.hpp"
#include "Confetti/SpawnPolicy/SpawnPolicy.hpp"

#include <memory>
#include <unordered_map>

namespace cft
{
	class ParticleRegistry
	{
	private:
		std::unordered_map<unsigned int, std::unique_ptr<ForceField>> m_forceFields;
		std::unordered_map<unsigned int, std::unique_ptr<ParticleBehavior>> m_particleBehaviors;
		std::unordered_map<unsigned int, std::unique_ptr<ParticleEmitterBehavior>> m_particleEmitterBehaviors;
		std::unordered_map<unsigned int, std::unique_ptr<ParticleSpawner>> m_particleSpawners;
		std::unordered_map<unsigned int, std::unique_ptr<SpawnPolicy>> m_spawnPolicies;
		std::unordered_map<unsigned int, ParticleEffect> m_particleEffects;
		std::unordered_map<unsigned int, ParticleEmitter> m_particleEmitters;

	public:
		void addForceField(unsigned int id, std::unique_ptr<ForceField> forceField);
		void addParticleBehavior(unsigned int id, std::unique_ptr<ParticleBehavior> particleBehavior);
		void addParticleEmitterBehavior(unsigned int id, std::unique_ptr<ParticleEmitterBehavior> particleEmitterBehavior);
		void addParticleSpawner(unsigned int id, std::unique_ptr<ParticleSpawner> particleSpawner);
		void addSpawnPolicy(unsigned int id, std::unique_ptr<SpawnPolicy> spawnPolicy);
		void addParticleEffect(unsigned int id, const ParticleEffect& particleEffect);
		void addParticleEmitter(unsigned int id, const ParticleEmitter& particleEmitter);

		void removeForceField(unsigned int id);
		void removeParticleBehavior(unsigned int id);
		void removeParticleEmitterBehavior(unsigned int id);
		void removeParticleSpawner(unsigned int id);
		void removeSpawnPolicy(unsigned int id);
		void removeParticleEffect(unsigned int id);
		void removeParticleEmitter(unsigned int id);

		const ForceField& getForceField(unsigned int id) const;
		const ParticleBehavior& getParticleBehavior(unsigned int id) const;
		const ParticleEmitterBehavior& getParticleEmitterBehavior(unsigned int id) const;
		const ParticleSpawner& getParticleSpawner(unsigned int id) const;
		const SpawnPolicy& getSpawnPolicy(unsigned int id) const;
		const ParticleEffect& getParticleEffect(unsigned int id) const;
		const ParticleEmitter& getParticleEmitter(unsigned int id) const;

		ForceField& getForceField(unsigned int id);
		ParticleBehavior& getParticleBehavior(unsigned int id);
		ParticleEmitterBehavior& getParticleEmitterBehavior(unsigned int id);
		ParticleSpawner& getParticleSpawner(unsigned int id);
		SpawnPolicy& getSpawnPolicy(unsigned int id);
		ParticleEffect& getParticleEffect(unsigned int id);
		ParticleEmitter& getParticleEmitter(unsigned int id);
	};
}