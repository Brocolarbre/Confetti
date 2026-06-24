#pragma once

#include "AssetRegistry.hpp"
#include "ParticleRegistry.hpp"
#include "ParticlePool.hpp"
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
		TimeRange timeRange;
		Transform transform;
		unsigned int particleRegistryId;
		std::unique_ptr<ParticleSpawner> particleSpawner;
		std::unique_ptr<SpawnPolicy> spawnPolicy;
		std::vector<std::unique_ptr<ForceField>> inheritedForceFields;
		std::vector<std::unique_ptr<MotionBehavior>> inheritedMotionBehaviors;
	};

	class ParticleSimulation
	{
	private:
		AssetRegistry& m_assetRegistry;
		RandomNumberGenerator& m_randomNumberGenerator;

		std::vector<ParticleEffectInstance> m_particleEffectInstances;
		std::vector<ParticleEmitterInstance> m_particleEmitterInstances;

		std::unordered_map<unsigned int, ParticlePool> m_particlePools;
		ParticleRegistry m_particleRegistry;

		ParticleEmitterInstance createParticleEmitter(const ParticleEmitterDescriptor& descriptor, const Transform& parentTransform, unsigned int recursionDepth, float elapsedTime);

	public:
		ParticleSimulation(AssetRegistry& assetRegistry, RandomNumberGenerator& randomNumberGenerator);

		const std::unordered_map<unsigned int, ParticlePool>& getParticlePools() const;
		const ParticleRegistry& getParticleRegistry() const;

		void addParticleEffect(float elapsedTime, unsigned int id);

		void clear();
		void update(float elapsedTime, float deltaTime);
	};
}