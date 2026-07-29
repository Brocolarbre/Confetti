#pragma once

#include "ParticleEffectInstance.hpp"
#include "ParticleEmitterInstance.hpp"
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
	class CONFETTI_API ParticleSimulation
	{
	private:
		AssetRegistry& m_assetRegistry;
		std::uint64_t m_seed;
		unsigned int m_totalEmitterSpawnCount;

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

		ParticleEmitterInstance createParticleEmitter(const ParticleEmitterSpawnContext& emitterSpawnContext, const MotionState& parentMotionState, std::optional<std::uint64_t> parentSeed, unsigned int recursionDepth, float elapsedTime);
		
		static std::uint64_t calculateInstanceSeed(std::uint64_t emitterSeed, unsigned int effectId, std::optional<std::uint64_t> baseSeed, std::optional<unsigned int> instanceIndex);

		template <typename T, typename Getter>
		static std::unique_ptr<T> instantiateElement(std::uint64_t emitterSeed, unsigned int elementId, std::optional<unsigned int> instanceIndex, Getter&& getElement);

		template <typename T, typename Getter>
		static std::vector<std::unique_ptr<T>> instantiateElements(std::uint64_t emitterSeed, const std::vector<unsigned int>& elementIds, Getter&& getElement);

	public:
		ParticleSimulation(AssetRegistry& assetRegistry);

		const std::unordered_map<unsigned int, ParticlePool>& getParticlePools() const;
		const std::unordered_map<unsigned int, TrailPool>& getTrailPools() const;
		const std::unordered_map<unsigned int, RibbonPool>& getRibbonPools() const;

		const ParticleRegistry& getParticleRegistry() const;
		const TrailRegistry& getTrailRegistry() const;
		const RibbonRegistry& getRibbonRegistry() const;

		void setSeed(std::uint64_t seed);

		void addParticleEffect(float elapsedTime, unsigned int id);

		void clear();
		void update(float elapsedTime, float deltaTime);
	};

	template <typename T, typename Getter>
	inline std::unique_ptr<T> ParticleSimulation::instantiateElement(std::uint64_t emitterSeed, unsigned int elementId, std::optional<unsigned int> instanceIndex, Getter&& getElement)
	{
		std::unique_ptr<T> element = getElement(elementId).clone();
		element->setSeed(calculateInstanceSeed(emitterSeed, elementId, element->getSeed(), instanceIndex));

		return element;
	}

	template <typename T, typename Getter>
	std::vector<std::unique_ptr<T>> ParticleSimulation::instantiateElements(std::uint64_t emitterSeed, const std::vector<unsigned int>& elementIds, Getter&& getElement)
	{
		std::unordered_map<unsigned int, unsigned int> elementIdCounts;

		std::vector<std::unique_ptr<T>> elements;
		elements.reserve(elementIds.size());

		for (unsigned int elementId : elementIds)
		{
			unsigned int instanceIndex = elementIdCounts[elementId]++;
			elements.push_back(instantiateElement<T>(emitterSeed, elementId, instanceIndex, getElement));
		}

		return elements;
	}
}