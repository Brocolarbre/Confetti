#pragma once

#include "Confetti/Particle/Ribbon.hpp"

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
		std::vector<std::deque<TrailPoint>> m_ribbonPoints;

		std::unordered_map<unsigned int, std::unordered_set<unsigned int>> m_pointConnexions;

		unsigned int m_capacity;
		unsigned int m_reservedCapacity;
		unsigned int m_count;

		void resize(unsigned int capacity);

	public:
		RibbonPool();
		
		const std::vector<unsigned int>& getRibbonRegistryId() const;
		const std::vector<unsigned int>& getFromParticleId() const;
		const std::vector<unsigned int>& getToParticleId() const;
		const std::vector<float>& getSpawnTime() const;
		const std::vector<std::deque<TrailPoint>>& getRibbonPoints() const;

		std::vector<unsigned int>& getRibbonRegistryId();
		std::vector<unsigned int>& getFromParticleId();
		std::vector<unsigned int>& getToParticleId();
		std::vector<float>& getSpawnTime();
		std::vector<std::deque<TrailPoint>>& getRibbonPoints();

		std::unordered_set<unsigned int>& getPointConnexions(unsigned int particleId);
		unsigned int getCount() const;

		void reserve(unsigned int capacity);
		void insert(const Ribbon& ribbon);
		void remove(unsigned int index);
	};
}