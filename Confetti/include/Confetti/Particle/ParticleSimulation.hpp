#pragma once

#include "ParticlePool.hpp"
#include "ParticleRegistry.hpp"

namespace cft
{
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