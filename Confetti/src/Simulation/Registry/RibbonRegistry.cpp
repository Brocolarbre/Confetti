#include "Confetti/Simulation/Registry/RibbonRegistry.hpp"

namespace cft
{
	RibbonRegistry::RibbonRegistry() :
		m_entries(),
		m_nextId(0)
	{

	}

	std::unordered_map<unsigned int, RibbonRegistryEntry>& RibbonRegistry::getEntries()
	{
		return m_entries;
	}

	const RibbonRegistryEntry& RibbonRegistry::getEntry(unsigned int id) const
	{
		return m_entries.at(id);
	}

	RibbonRegistryEntry& RibbonRegistry::getEntry(unsigned int id)
	{
		return m_entries.at(id);
	}

	void RibbonRegistry::clear()
	{
		m_entries.clear();
		m_nextId = 0;
	}

	unsigned int RibbonRegistry::createEntry(unsigned int poolId, const RibbonConfiguration& ribbonConfiguration, std::unique_ptr<ParticleLinker> particleLinker)
	{
		unsigned int id = m_nextId++;
		m_entries.insert({ id, RibbonRegistryEntry{ 0, poolId, ribbonConfiguration, std::move(particleLinker) } });

		return id;
	}

	void RibbonRegistry::addReferenceCount(unsigned int id, int referenceCount)
	{
		auto entry = m_entries.find(id);
		if (entry == m_entries.end())
			return;

		entry->second.count += referenceCount;

		if (entry->second.count <= 0)
			m_entries.erase(id);
	}
}