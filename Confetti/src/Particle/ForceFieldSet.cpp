#include "Confetti/Particle/ForceFieldSet.hpp"

namespace cft
{
	ForceFieldSet::ForceFieldSet() :
		m_forceFieldEntries(),
		m_nextId(0)
	{

	}

	void ForceFieldSet::clear()
	{
		m_forceFieldEntries.clear();
		m_nextId = 0;
	}

	const std::vector<unsigned int>& ForceFieldSet::getForceFieldIds(unsigned int id) const
	{
		return m_forceFieldEntries.at(id).forceFieldIds;
	}

	unsigned int ForceFieldSet::createForceFieldSetEntry(const std::vector<unsigned int>& forceFieldIds)
	{
		unsigned int id = m_nextId++;
		m_forceFieldEntries[id] = ForceFieldSetEntry{ forceFieldIds, 0 };

		return id;
	}

	void ForceFieldSet::addForceFieldReferenceCount(unsigned int id, int referenceCount)
	{
		auto forceFieldEntry = m_forceFieldEntries.find(id);
		if (forceFieldEntry == m_forceFieldEntries.end())
			return;

		forceFieldEntry->second.count += referenceCount;

		if (forceFieldEntry->second.count <= 0)
			m_forceFieldEntries.erase(id);
	}
}