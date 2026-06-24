#pragma once

#include "Confetti/Particle/RenderDescriptor.hpp"
#include "Confetti/Particle/SpawnTrigger.hpp"
#include "Confetti/ForceField/ForceField.hpp"
#include "Confetti/MotionBehavior/MotionBehavior.hpp"
#include "Confetti/ParticleBehavior/ParticleBehavior.hpp"

#include <optional>
#include <unordered_map>

namespace cft
{
	struct ParticleRegistryEntry
	{
		int count;
		unsigned int pool;
		unsigned int recursionDepth;
		std::optional<SpawnTrigger> spawnTrigger;
		RenderDescriptor renderDescriptor;
		std::vector<std::unique_ptr<ForceField>> forceFields;
		std::vector<std::unique_ptr<MotionBehavior>> motionBehaviors;
		std::vector<std::unique_ptr<ParticleBehavior>> particleBehaviors;
	};

	class ParticleRegistry
	{
	private:
		std::unordered_map<unsigned int, ParticleRegistryEntry> m_entries;
		unsigned int m_nextId;

	public:
		ParticleRegistry();

		void clear();
		const ParticleRegistryEntry& getEntry(unsigned int id) const;
		unsigned int createEntry(unsigned int pool, unsigned int recursionDepth, const std::optional<SpawnTrigger>& spawnTrigger, const RenderDescriptor& renderDescriptor, std::vector<std::unique_ptr<ForceField>> forceFields, std::vector<std::unique_ptr<MotionBehavior>>& motionBehaviors, std::vector<std::unique_ptr<ParticleBehavior>>& particleBehaviors);
		void addReferenceCount(unsigned int id, int referenceCount);
	};
}