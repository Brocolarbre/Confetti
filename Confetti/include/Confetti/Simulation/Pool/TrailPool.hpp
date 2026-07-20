#pragma once

#include "Confetti/Simulation/Core/Trail.hpp"

namespace cft
{
	class TrailPool
	{
	private:
		std::vector<unsigned int> m_trailRegistryId;
		std::vector<unsigned int> m_particleId;
		std::vector<float> m_particleDeathTime;
		std::vector<glm::vec4> m_particleColor;
		std::vector<std::deque<PathPoint>> m_trailPoints;

		unsigned int m_storageCapacity;
		unsigned int m_reservedSlots;
		unsigned int m_count;

		void resizeStorage(unsigned int capacity);

	public:
		TrailPool();

		const std::vector<unsigned int>& getTrailRegistryId() const;
		const std::vector<unsigned int>& getParticleId() const;
		const std::vector<float>& getParticleDeathTime() const;
		const std::vector<glm::vec4>& getParticleColor() const;
		const std::vector<std::deque<PathPoint>>& getPathPoints() const;

		std::vector<unsigned int>& getTrailRegistryId();
		std::vector<unsigned int>& getParticleId();
		std::vector<float>& getParticleDeathTime();
		std::vector<glm::vec4>& getParticleColor();
		std::vector<std::deque<PathPoint>>& getPathPoints();

		unsigned int getCount() const;

		void reserveSlots(unsigned int slots);
		void insert(const Trail& trail);
		void remove(unsigned int index);
	};
}