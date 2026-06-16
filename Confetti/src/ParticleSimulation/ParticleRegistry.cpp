#include "Confetti/ParticleSimulation/ParticleRegistry.hpp"

namespace cft
{
	ParticleRegistry::ParticleRegistry() :
		m_entries(),
		m_nextId(0)
	{

	}

	void ParticleRegistry::clear()
	{
		m_entries.clear();
		m_nextId = 0;
	}

	const ParticleRegistryEntry& ParticleRegistry::getEntry(unsigned int id) const
	{
		return m_entries.at(id);
	}

	unsigned int ParticleRegistry::createEntry(unsigned int pool, const RenderDescriptor& renderDescriptor, std::vector<std::unique_ptr<ForceField>> forceFields, std::vector<std::unique_ptr<MotionBehavior>>& motionBehaviors, std::vector<std::unique_ptr<ParticleBehavior>>& particleBehaviors)
	{
		unsigned int id = m_nextId++;
		m_entries.insert({ id, ParticleRegistryEntry{ 0, pool, renderDescriptor, std::move(forceFields), std::move(motionBehaviors), std::move(particleBehaviors) }});

		return id;
	}

	void ParticleRegistry::addReferenceCount(unsigned int id, int referenceCount)
	{
		auto entry = m_entries.find(id);
		if (entry == m_entries.end())
			return;

		entry->second.count += referenceCount;

		if (entry->second.count <= 0)
			m_entries.erase(id);
	}
}