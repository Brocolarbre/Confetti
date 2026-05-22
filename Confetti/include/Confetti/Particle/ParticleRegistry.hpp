#pragma once

#include "ParticleGenerator.hpp"
#include "Confetti/ForceField/ForceField.hpp"

#include <memory>
#include <unordered_map>

namespace cft
{
	struct TimeRange
	{
		float spawnTime;
		float duration;
	};

	struct ParticleEmitterClip
	{
		unsigned int emitterId;
		TimeRange timeRange;
		std::vector<unsigned int> forceFields;
	};

	struct ParticleEffectClip
	{
		unsigned int effectId;
		TimeRange timeRange;
		std::vector<unsigned int> forceFields;
	};

	struct ParticleSystemClip
	{
		unsigned int systemId;
		TimeRange timeRange;
		std::vector<unsigned int> forceFields;
	};

	struct ParticleEmitter
	{
		unsigned int group;
		float spawnRate;
		ParticleBoundaries boundaries; // SpawnBehavior
	};

	struct ParticleEffect
	{
		std::vector<ParticleEmitterClip> emitters;
	};

	struct ParticleSystem
	{
		std::vector<ParticleEffectClip> effects;
	};

	struct ParticleEmitterInstance
	{
		TimeRange timeRange;
		std::vector<unsigned int> forceFields;
		unsigned int forceFieldSetId;
		unsigned int group;
		float spawnRate;
		float accumulator;
		ParticleBoundaries boundaries;
	};

	struct ParticleEffectInstance
	{
		TimeRange timeRange;
		std::vector<unsigned int> forceFields;
		std::vector<ParticleEmitterClip> emittersToSpawn;
	};

	struct ParticleSystemInstance
	{
		TimeRange timeRange;
		std::vector<unsigned int> forceFields;
		std::vector<ParticleEffectClip> effectsToSpawn;
	};

	class ParticleRegistry
	{
	private:
		std::unordered_map<unsigned int, ParticleSystem> m_particleSystems;
		std::unordered_map<unsigned int, ParticleEffect> m_particleEffects;
		std::unordered_map<unsigned int, ParticleEmitter> m_particleEmitters;
		std::unordered_map<unsigned int, std::unique_ptr<ForceField>> m_forceFields;

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

		ParticleSystem& getParticleSystem(unsigned int id);
		ParticleEffect& getParticleEffect(unsigned int id);
		ParticleEmitter& getParticleEmitter(unsigned int id);
		ForceField& getForceField(unsigned int id);
	};
}