#pragma once

#include "Confetti/Data/RibbonConfiguration.hpp"
#include "Confetti/Simulation/Link/ParticleLinker/ParticleLinker.hpp"
#include "Confetti/Simulation/Link/RibbonGenerator/RibbonGenerator.hpp"

#include <memory>
#include <unordered_map>

namespace cft
{
	struct RibbonRegistryEntry
	{
		unsigned int count;
		unsigned int poolId;
		RibbonConfiguration ribbonConfiguration;
		std::unique_ptr<ParticleLinker> particleLinker;
		std::unique_ptr<RibbonGenerator> ribbonGenerator;
	};

	class RibbonRegistry
	{
	private:
		std::unordered_map<unsigned int, RibbonRegistryEntry> m_entries;
		unsigned int m_nextId;

	public:
		RibbonRegistry();

		std::unordered_map<unsigned int, RibbonRegistryEntry>& getEntries();

		const RibbonRegistryEntry& getEntry(unsigned int id) const;
		RibbonRegistryEntry& getEntry(unsigned int id);

		void clear();

		unsigned int createEntry(unsigned int poolId, const RibbonConfiguration& ribbonConfiguration, std::unique_ptr<ParticleLinker> particleLinker, std::unique_ptr<RibbonGenerator> ribbonGenerator);
		void addReferenceCount(unsigned int id, int referenceCount);
	};
}