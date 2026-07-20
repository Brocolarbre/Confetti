#pragma once

#include "ParticleEffectInstance.hpp"
#include "ParticleEmitterInstance.hpp"
#include "PathPoint.hpp"
#include "Confetti/Simulation/Pool/ParticlePool.hpp"
#include "Confetti/Simulation/Pool/RibbonPool.hpp"
#include "Confetti/Simulation/Pool/TrailPool.hpp"
#include "Confetti/Simulation/Registry/AssetRegistry.hpp"
#include "Confetti/Simulation/Registry/ParticleRegistry.hpp"
#include "Confetti/Simulation/Registry/RibbonRegistry.hpp"
#include "Confetti/Simulation/Registry/TrailRegistry.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

#include <deque>

namespace cft
{
	class ParticleSimulation
	{
	private:
		AssetRegistry& m_assetRegistry;
		RandomNumberGenerator& m_randomNumberGenerator;

		std::vector<ParticleEffectInstance> m_particleEffectInstances;
		std::vector<ParticleEmitterInstance> m_particleEmitterInstances;

		std::unordered_map<unsigned int, ParticlePool> m_particlePools;
		std::unordered_map<unsigned int, TrailPool> m_trailPools;
		std::unordered_map<unsigned int, RibbonPool> m_ribbonPools;

		ParticleRegistry m_particleRegistry;
		TrailRegistry m_trailRegistry;
		RibbonRegistry m_ribbonRegistry;

		void updateParticleEffects(float elapsedTime, float deltaTime);
		void updateParticleEmitters(float elapsedTime, float deltaTime);
		void updateParticles(float elapsedTime, float deltaTime);
		void updateTrails(float elapsedTime, float deltaTime);
		void updateRibbons(float elapsedTime, float deltaTime);

		ParticleEmitterInstance createParticleEmitter(const ParticleEmitterSpawnContext& emitterSpawnContext, const MotionState& parentMotionState, unsigned int recursionDepth, float elapsedTime);

	public:
		ParticleSimulation(AssetRegistry& assetRegistry, RandomNumberGenerator& randomNumberGenerator);

		const std::unordered_map<unsigned int, ParticlePool>& getParticlePools() const;
		const std::unordered_map<unsigned int, TrailPool>& getTrailPools() const;
		const std::unordered_map<unsigned int, RibbonPool>& getRibbonPools() const;

		const ParticleRegistry& getParticleRegistry() const;
		const TrailRegistry& getTrailRegistry() const;
		const RibbonRegistry& getRibbonRegistry() const;

		void addParticleEffect(float elapsedTime, unsigned int id);

		void clear();
		void update(float elapsedTime, float deltaTime);
	};
}