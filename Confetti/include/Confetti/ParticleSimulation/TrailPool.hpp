#pragma once

#include "Confetti/Particle/Trail.hpp"

namespace cft
{
	class TrailPool
	{
	private:
		std::vector<unsigned int> m_trailRegistryId;
		std::vector<unsigned int> m_particleId;
		std::vector<float> m_particleDeathTime;
		std::vector<glm::vec4> m_particleColor;
		std::vector<std::deque<TrailPoint>> m_trailPoints; // Replace with ring buffer ?

		unsigned int m_capacity;
		unsigned int m_reservedCapacity;
		unsigned int m_count;

		void resize(unsigned int capacity);

	public:
		TrailPool();

		const std::vector<unsigned int>& getTrailRegistryId() const;
		const std::vector<unsigned int>& getParticleId() const;
		const std::vector<float>& getParticleDeathTime() const;
		const std::vector<glm::vec4>& getParticleColor() const;
		const std::vector<std::deque<TrailPoint>>& getTrailPoints() const;

		std::vector<unsigned int>& getTrailRegistryId();
		std::vector<unsigned int>& getParticleId();
		std::vector<float>& getParticleDeathTime();
		std::vector<glm::vec4>& getParticleColor();
		std::vector<std::deque<TrailPoint>>& getTrailPoints();

		unsigned int getCount() const;

		void reserve(unsigned int capacity);
		void insert(const Trail& trail);
		void remove(unsigned int index);
	};
}