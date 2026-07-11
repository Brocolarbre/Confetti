#pragma once

#include "AssetRegistry.hpp"
#include "ParticleRegistry.hpp"
#include "ParticlePool.hpp"
#include "TrailPool.hpp"
#include "TrailRegistry.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	struct ParticleEffectInstance
	{
		float spawnTime;
		std::vector<ParticleEmitterDescriptor> emitterDescriptors;
	};

	struct ParticleEmitterInstance
	{
		TimeRange timeRange;
		MotionState motionState;
		glm::vec3 postBehaviorPosition;
		unsigned int particleRegistryId;
		std::optional<unsigned int> trailRegistryId;
		std::unique_ptr<ParticleSpawner> particleSpawner;
		std::unique_ptr<EmissionPattern> emissionPattern;
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
		std::unordered_map<unsigned int, TrailPool> m_trailPools;
		ParticleRegistry m_particleRegistry;
		TrailRegistry m_trailRegistry;

		ParticleEmitterInstance createParticleEmitter(const ParticleEmitterDescriptor& descriptor, const MotionState& parentMotionState, unsigned int recursionDepth, float elapsedTime);

	public:
		ParticleSimulation(AssetRegistry& assetRegistry, RandomNumberGenerator& randomNumberGenerator);

		const std::unordered_map<unsigned int, ParticlePool>& getParticlePools() const;
		const std::unordered_map<unsigned int, TrailPool>& getTrailPools() const;
		const ParticleRegistry& getParticleRegistry() const;
		const TrailRegistry& getTrailRegistry() const;

		void addParticleEffect(float elapsedTime, unsigned int id);

		void clear();
		void update(float elapsedTime, float deltaTime);
	};
}