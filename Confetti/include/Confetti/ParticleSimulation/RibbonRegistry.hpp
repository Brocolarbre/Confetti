#pragma once

#include "Confetti/Particle/RibbonConfiguration.hpp"
#include "Confetti/RibbonGenerator/RibbonGenerator.hpp"

#include <memory>
#include <unordered_map>

namespace cft
{
	struct RibbonRegistryEntry
	{
		int count; // unsigned int ?
		unsigned int poolId;
		RibbonConfiguration ribbonConfiguration;
		std::unique_ptr<RibbonGenerator> ribbonGenerator;
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

		unsigned int createEntry(unsigned int poolId, const RibbonConfiguration& ribbonConfiguration);
		void addReferenceCount(unsigned int id, int referenceCount);
	};
}