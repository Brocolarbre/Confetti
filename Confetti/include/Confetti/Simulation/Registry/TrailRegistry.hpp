#pragma once

#include "Confetti/Data/TrailConfiguration.hpp"

#include <unordered_map>

namespace cft
{
	struct TrailRegistryEntry
	{
		int count;
		TrailConfiguration trailConfiguration;
	};

	class TrailRegistry
	{
	private:
		std::unordered_map<unsigned int, TrailRegistryEntry> m_entries;
		unsigned int m_nextId;

	public:
		TrailRegistry();

		void clear();

		const TrailRegistryEntry& getEntry(unsigned int id) const;
		TrailRegistryEntry& getEntry(unsigned int id);

		unsigned int createEntry(const TrailConfiguration& trailConfiguration);
		void addReferenceCount(unsigned int id, int referenceCount);
	};
}