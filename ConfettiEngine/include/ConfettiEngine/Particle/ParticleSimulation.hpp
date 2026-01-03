#pragma once

#include "ParticlePool.hpp"
#include "ParticleGenerator.hpp"

#include <unordered_map>

namespace cft
{
	struct ParticleEmitter
	{
		unsigned int effectId;
		unsigned int type;
		float spawnTime;
		float lifetime;
		float spawnRate;
		float accumulator;
		ParticleBoundaries boundaries;
	};

	struct ParticleEffect
	{
		unsigned int systemId;
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

	class ParticleRegistry
	{
	private:
		std::unordered_map<unsigned int, ParticleSystem> m_particleSystems;
		std::unordered_map<unsigned int, ParticleEffect> m_particleEffects;
		std::unordered_map<unsigned int, ParticleEmitter> m_particleEmitters;

	public:
		void addParticleSystem(unsigned int id, const ParticleSystem& particleSystem);
		void addParticleEffect(unsigned int id, const ParticleEffect& particleEffect);
		void addParticleEmitter(unsigned int id, const ParticleEmitter& particleEmitter);

		void removeParticleSystem(unsigned int id);
		void removeParticleEffect(unsigned int id);
		void removeParticleEmitter(unsigned int id);

		const ParticleSystem& getParticleSystem(unsigned int id) const;
		const ParticleEffect& getParticleEffect(unsigned int id) const;
		const ParticleEmitter& getParticleEmitter(unsigned int id) const;
	};

	class ParticleSimulation
	{
	private:
		ParticleRegistry m_particleRegistry;
		RandomNumberGenerator m_randomNumberGenerator;
		std::unordered_map<unsigned int, ParticlePool> m_particlePools;
		std::vector<ParticleSystem> m_particleSystems;
		std::vector<ParticleEffect> m_particleEffects;
		std::vector<ParticleEmitter> m_particleEmitters;

	public:
		ParticleSimulation();

		ParticleRegistry& getParticleRegistry();
		const std::unordered_map<unsigned int, ParticlePool>& getParticlePools() const;

		void setSeed(unsigned int seed);
		void addParticleSystem(unsigned int id);
		void clear();

		// void setProgress(float elapsedTime);
		void update(float elapsedTime, float deltaTime);
	};
}