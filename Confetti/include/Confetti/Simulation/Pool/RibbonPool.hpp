#pragma once

#include "Confetti/Simulation/Core/Ribbon.hpp"

#include <unordered_set>
#include <vector>

namespace cft
{
	class RibbonPool
	{
	private:
		std::vector<unsigned int> m_ribbonRegistryId;
		std::vector<unsigned int> m_fromParticleId;
		std::vector<unsigned int> m_toParticleId;
		std::vector<float> m_spawnTime;
		std::vector<std::deque<PathPoint>> m_ribbonPoints;

		std::unordered_map<unsigned int, std::unordered_set<unsigned int>> m_pointConnections;

		unsigned int m_storageCapacity;
		unsigned int m_reservedSlots;
		unsigned int m_count;

		void resizeStorage(unsigned int capacity);

	public:
		RibbonPool();
		
		const std::vector<unsigned int>& getRibbonRegistryId() const;
		const std::vector<unsigned int>& getFromParticleId() const;
		const std::vector<unsigned int>& getToParticleId() const;
		const std::vector<float>& getSpawnTime() const;
		const std::vector<std::deque<PathPoint>>& getRibbonPoints() const;

		std::vector<unsigned int>& getRibbonRegistryId();
		std::vector<unsigned int>& getFromParticleId();
		std::vector<unsigned int>& getToParticleId();
		std::vector<float>& getSpawnTime();
		std::vector<std::deque<PathPoint>>& getRibbonPoints();

		std::unordered_set<unsigned int>& getPointConnections(unsigned int particleId);
		unsigned int getCount() const;

		void reserveSlots(unsigned int slots);
		void insert(const Ribbon& ribbon);
		void remove(unsigned int index);
	};
}