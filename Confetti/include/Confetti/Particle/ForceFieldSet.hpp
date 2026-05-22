#pragma once

#include "Confetti/ForceField/ForceField.hpp"

#include <unordered_map>

namespace cft
{
	struct ForceFieldSetEntry
	{
		std::vector<std::reference_wrapper<ForceField>> forceFieldIds;
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
		const std::vector<std::reference_wrapper<ForceField>>& getForceFieldIds(unsigned int id) const;
		unsigned int createForceFieldSetEntry(const std::vector<std::reference_wrapper<ForceField>>& forceFieldIds);
		void addForceFieldReferenceCount(unsigned int id, int referenceCount);
	};
}