#include "Confetti/Simulation/Registry/ParticleRegistry.hpp"

namespace cft
{
	ParticleRegistry::ParticleRegistry() :
		m_entries(),
		m_nextId(0)
	{

	}

	std::unordered_map<unsigned int, ParticleRegistryEntry>& ParticleRegistry::getEntries()
	{
		return m_entries;
	}

	const ParticleRegistryEntry& ParticleRegistry::getEntry(unsigned int id) const
	{
		return m_entries.at(id);
	}

	ParticleRegistryEntry& ParticleRegistry::getEntry(unsigned int id)
	{
		return m_entries.at(id);
	}

	void ParticleRegistry::clear()
	{
		m_entries.clear();
		m_nextId = 0;
	}

	unsigned int ParticleRegistry::createEntry(unsigned int poolId, unsigned int recursionDepth, const std::optional<SpawnTriggerDescriptor>& spawnTriggerDescriptor, const RenderConfiguration& renderConfiguration, std::vector<std::unique_ptr<ForceField>> forceFields, std::vector<std::unique_ptr<MotionBehavior>>& motionBehaviors, std::vector<std::unique_ptr<VisualBehavior>>& visualBehaviors)
	{
		unsigned int id = m_nextId++;
		m_entries.insert({ id, ParticleRegistryEntry{ 0, poolId, recursionDepth, 0.0f, spawnTriggerDescriptor, renderConfiguration, std::move(forceFields), std::move(motionBehaviors), std::move(visualBehaviors) } });

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