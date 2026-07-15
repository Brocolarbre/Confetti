#pragma once

#include "Confetti/Particle/RibbonConfiguration.hpp"
#include "Confetti/ParticleConnector/ParticleConnector.hpp"

#include <memory>
#include <unordered_map>

namespace cft
{
	struct RibbonRegistryEntry
	{
		int count; // unsigned int ?
		unsigned int poolId;
		RibbonConfiguration ribbonConfiguration;
		std::unique_ptr<ParticleConnector> particleConnector;
	};

	class RibbonRegistry
	{
	private:
		std::unordered_map<unsigned int, RibbonRegistryEntry> m_entries;
		unsigned int m_nextId;

	public:
		RibbonRegistry();

		void clear();

		const RibbonRegistryEntry& getEntry(unsigned int id) const;
		RibbonRegistryEntry& getEntry(unsigned int id);

		unsigned int createEntry(unsigned int poolId, const RibbonConfiguration& ribbonConfiguration, std::unique_ptr<ParticleConnector> particleConnector);
		void addReferenceCount(unsigned int id, int referenceCount);
	};
}