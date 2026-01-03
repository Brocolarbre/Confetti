#pragma once

#include "ParticleGenerator.hpp"
#include "ForceField.hpp"

#include <memory>
#include <unordered_map>

namespace cft
{
	struct ParticleEmitter
	{
		unsigned int type;
		unsigned int instance;
		float spawnTime;
		float lifetime;
		float spawnRate;
		float accumulator;
		ParticleBoundaries boundaries;
	};

	struct ParticleEffect
	{
		float spawnTime;
		float lifetime;
		std::vector<unsigned int> emitters;
	};

	struct ParticleSystem
	{
		float spawnTime;
		float lifetime;
		std::vector<unsigned int> effects;
	};

	struct ParticleEntry
	{
		unsigned int parentType;
		unsigned int parentInstance;
		std::vector<unsigned int> forceFields;
	};

	class ParticleRegistry
	{
	private:
		std::unordered_map<unsigned int, ParticleSystem> m_particleSystems;
		std::unordered_map<unsigned int, ParticleEffect> m_particleEffects;
		std::unordered_map<unsigned int, ParticleEmitter> m_particleEmitters;
		std::unordered_map<unsigned int, std::unique_ptr<ForceField>> m_forceFields;

		std::unordered_map<unsigned int, std::unordered_map<unsigned int, std::vector<unsigned int>>> m_particleSystemEntries;
		std::unordered_map<unsigned int, std::unordered_map<unsigned int, ParticleEntry>> m_particleEffectEntries;
		std::unordered_map<unsigned int, std::unordered_map<unsigned int, ParticleEntry>> m_particleEmitterEntries;

	public:
		void addParticleSystem(unsigned int id, const ParticleSystem& particleSystem);
		void addParticleEffect(unsigned int id, const ParticleEffect& particleEffect);
		void addParticleEmitter(unsigned int id, const ParticleEmitter& particleEmitter);
		void addForceField(unsigned int id, std::unique_ptr<ForceField> forceField);

		void removeParticleSystem(unsigned int id);
		void removeParticleEffect(unsigned int id);
		void removeParticleEmitter(unsigned int id);
		void removeForceField(unsigned int id);

		const ParticleSystem& getParticleSystem(unsigned int id) const;
		const ParticleEffect& getParticleEffect(unsigned int id) const;
		const ParticleEmitter& getParticleEmitter(unsigned int id) const;
		const ForceField& getForceField(unsigned int id) const;

		void addParticleSystemEntry(unsigned int type, unsigned int instance, const std::vector<unsigned int>& entry);
		void addParticleEffectEntry(unsigned int type, unsigned int instance, const ParticleEntry& entry);
		void addParticleEmitterEntry(unsigned int type, unsigned int instance, const ParticleEntry& entry);

		void removeParticleSystemEntry(unsigned int type, unsigned int instance);
		void removeParticleEffectEntry(unsigned int type, unsigned int instance);
		void removeParticleEmitterEntry(unsigned int type, unsigned int instance);

		const std::vector<unsigned int>& getParticleSystemEntry(unsigned int type, unsigned int instance) const;
		const ParticleEntry& getParticleEffectEntry(unsigned int type, unsigned int instance) const;
		const ParticleEntry& getParticleEmitterEntry(unsigned int type, unsigned int instance) const;
	};
}