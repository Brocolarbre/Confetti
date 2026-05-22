#pragma once

#include <unordered_map>

namespace cft
{
	struct ForceFieldSetEntry
	{
		std::vector<unsigned int> forceFieldIds;
		int count;
	};

	class ForceFieldSet
	{
	private:
		std::unordered_map<unsigned int, ForceFieldSetEntry> m_forceFieldEntries;
		unsigned int m_nextId;

	public:
		ForceFieldSet();

		void clear();
		const std::vector<unsigned int>& getForceFieldIds(unsigned int id) const;
		unsigned int createForceFieldSetEntry(const std::vector<unsigned int>& forceFieldIds);
		void addForceFieldReferenceCount(unsigned int id, int referenceCount);
	};
}