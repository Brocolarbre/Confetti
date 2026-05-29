#pragma once

#include "Confetti/ForceField/ForceField.hpp"
#include "Confetti/ParticleBehavior/ParticleBehavior.hpp"

#include <unordered_map>

namespace cft
{
	struct ParticlePropertySetEntry
	{
		std::vector<std::unique_ptr<ForceField>> forceFields;
		std::unique_ptr<ParticleBehavior> particleBehavior;
		int count;
	};

	class ParticlePropertySet
	{
	private:
		std::unordered_map<unsigned int, ParticlePropertySetEntry> m_entries;
		unsigned int m_nextId;

	public:
		ParticlePropertySet();

		void clear();
		const ParticlePropertySetEntry& getEntry(unsigned int id) const;
		unsigned int createEntry(std::vector<std::unique_ptr<ForceField>> forceFields, std::unique_ptr<ParticleBehavior> particleBehavior);
		void addReferenceCount(unsigned int id, int referenceCount);
	};
}