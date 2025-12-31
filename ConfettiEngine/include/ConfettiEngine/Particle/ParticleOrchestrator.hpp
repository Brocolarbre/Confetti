#pragma once

#include "ParticleEffectPool.hpp"
#include "ParticleEmitterPool.hpp"

#include <unordered_map>

namespace cft
{
	class ParticleSimulation;

	struct ParticleSystem
	{
		std::vector<unsigned int> effects;
	};

	class ParticleOrchestrator
	{
	private:
		std::vector<unsigned int> m_effects;
		ParticleEffectPool m_particleEffectPool;
		std::unordered_map<unsigned int, ParticleEmitterPool> m_particleEmitterPools;
		ParticleSimulation& m_particleSimulation;

		void createParticleEffect(const ParticleEffect& particleEffect);

	public:
		ParticleOrchestrator(ParticleSimulation& particleSimulation);

		const std::unordered_map<unsigned int, ParticleEmitterPool>& getParticleEmitterPools() const;
		const ParticleEmitter& getParticleEmitter(unsigned int id) const;

		void createParticleEmitter(const ParticleEmitter& particleEmitter);
		void addParticleSystem(const ParticleSystem& particleSystem);

		void update(float elapsedTime, float deltaTime);
	};
}