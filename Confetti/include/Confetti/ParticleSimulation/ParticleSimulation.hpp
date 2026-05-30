#pragma once

#include "ParticlePropertySet.hpp"
#include "ParticlePool.hpp"
#include "ParticleRegistry.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	struct ParticleEffectInstance
	{
		float spawnTime;
		std::vector<ParticleEmitterDescriptor> emitters;
	};

	struct ParticleEmitterInstance
	{
		std::unique_ptr<ParticleSpawner> particleSpawner;
		std::unique_ptr<SpawnPolicy> spawnPolicy;
		std::unique_ptr<ParticleEmitterBehavior> emitterBehavior;
		TimeRange timeRange;
		unsigned int pool;
		unsigned int id;
		glm::vec3 position;
		glm::vec3 velocity;
	};

	class ParticleSimulation
	{
	private:
		ParticleRegistry& m_particleRegistry;
		RandomNumberGenerator& m_randomNumberGenerator;

		std::vector<ParticleEffectInstance> m_particleEffectInstances;
		std::vector<ParticleEmitterInstance> m_particleEmitterInstances;

		std::unordered_map<unsigned int, ParticlePool> m_particlePools;
		ParticlePropertySet m_particleProperties;

	public:
		ParticleSimulation(ParticleRegistry& particleRegistry, RandomNumberGenerator& randomNumberGenerator);

		const std::unordered_map<unsigned int, ParticlePool>& getParticlePools() const;

		void setSeed(unsigned int seed);
		void addParticleEffect(float elapsedTime, unsigned int id);

		void clear();
		void update(float elapsedTime, float deltaTime);
	};
}