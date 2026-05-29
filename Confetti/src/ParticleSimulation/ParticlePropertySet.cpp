#include "Confetti/ParticleSimulation/ParticlePropertySet.hpp"

namespace cft
{
	ParticlePropertySet::ParticlePropertySet() :
		m_entries(),
		m_nextId(0)
	{

	}

	void ParticlePropertySet::clear()
	{
		m_entries.clear();
		m_nextId = 0;
	}

	const ParticlePropertySetEntry& ParticlePropertySet::getEntry(unsigned int id) const
	{
		return m_entries.at(id);
	}

	unsigned int ParticlePropertySet::createEntry(std::vector<std::unique_ptr<ForceField>> forceFields, std::unique_ptr<ParticleBehavior> particleBehavior)
	{
		unsigned int id = m_nextId++;
		m_entries.insert({ id, ParticlePropertySetEntry{ std::move(forceFields), std::move(particleBehavior), 0 } });

		return id;
	}

	void ParticlePropertySet::addReferenceCount(unsigned int id, int referenceCount)
	{
		auto entry = m_entries.find(id);
		if (entry == m_entries.end())
			return;

		entry->second.count += referenceCount;

		if (entry->second.count <= 0)
			m_entries.erase(id);
	}
}