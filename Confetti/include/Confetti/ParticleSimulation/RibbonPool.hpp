#pragma once

#include "Confetti/Particle/Ribbon.hpp"

#include <vector>

namespace cft
{
	class RibbonPool
	{
	private:
		std::vector<unsigned int> m_ribbonRegistryId;
		std::vector<unsigned int> m_fromParticleId;
		std::vector<unsigned int> m_toParticleId;

		unsigned int m_capacity;
		unsigned int m_reservedCapacity;
		unsigned int m_count;

		void resize(unsigned int capacity);

	public:
		RibbonPool();
		
		const std::vector<unsigned int>& getRibbonRegistryId() const;
		const std::vector<unsigned int>& getFromParticleId() const;
		const std::vector<unsigned int>& getToParticleId() const;

		std::vector<unsigned int>& getRibbonRegistryId();
		std::vector<unsigned int>& getFromParticleId();
		std::vector<unsigned int>& getToParticleId();

		unsigned int getCount() const;

		void reserve(unsigned int capacity);
		void insert(const Ribbon& ribbon);
		void remove(unsigned int index);
	};
}