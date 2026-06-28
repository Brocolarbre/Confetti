#include "Confetti/ParticleSimulation/TrailRegistry.hpp"

namespace cft
{
	TrailRegistry::TrailRegistry() :
		m_entries(),
		m_nextId(0)
	{

	}

	void TrailRegistry::clear()
	{
		m_entries.clear();
		m_nextId = 0;
	}

	const TrailRegistryEntry& TrailRegistry::getEntry(unsigned int id) const
	{
		return m_entries.at(id);
	}

	TrailRegistryEntry& TrailRegistry::getEntry(unsigned int id)
	{
		return m_entries.at(id);
	}

	unsigned int TrailRegistry::createEntry(const TrailConfiguration& trailConfiguration)
	{
		unsigned int id = m_nextId++;
		m_entries.insert({ id, TrailRegistryEntry{ 0, trailConfiguration } });

		return id;
	}

	void TrailRegistry::addReferenceCount(unsigned int id, int referenceCount)
	{
		auto entry = m_entries.find(id);
		if (entry == m_entries.end())
			return;

		entry->second.count += referenceCount;

		if (entry->second.count <= 0)
			m_entries.erase(id);
	}
}