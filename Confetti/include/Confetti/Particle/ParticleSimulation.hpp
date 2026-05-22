#pragma once

#include "ForceFieldSet.hpp"
#include "ParticlePool.hpp"
#include "ParticleRegistry.hpp"

namespace cft
{
	class ParticleSimulation
	{
	private:
		ParticleRegistry m_particleRegistry;
		RandomNumberGenerator m_randomNumberGenerator;

		std::vector<ParticleSystemClip> m_particleSystemClips;

		std::vector<ParticleSystemInstance> m_particleSystemInstances;
		std::vector<ParticleEffectInstance> m_particleEffectInstances;
		std::vector<ParticleEmitterInstance> m_particleEmitterInstances;

		std::unordered_map<unsigned int, ParticlePool> m_particlePools;
		ForceFieldSet m_forceFieldSet;

	public:
		ParticleSimulation();

		ParticleRegistry& getParticleRegistry();
		const std::unordered_map<unsigned int, ParticlePool>& getParticlePools() const;

		void addParticleSystemClip(const ParticleSystemClip& clip);
		void removeParticleSystemClip(unsigned int index);

		void setSeed(unsigned int seed);

		void clear();
		void start();
		// void setProgress(float elapsedTime);
		void update(float elapsedTime, float deltaTime);
	};
}