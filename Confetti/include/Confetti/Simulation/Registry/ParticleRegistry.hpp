#pragma once

#include "Confetti/Data/RenderConfiguration.hpp"
#include "Confetti/Data/SpawnTriggerDescriptor.hpp"
#include "Confetti/Data/TrailConfiguration.hpp"
#include "Confetti/Behavior/Force/ForceField.hpp"
#include "Confetti/Behavior/Motion/MotionBehavior.hpp"
#include "Confetti/Behavior/Visual/VisualBehavior.hpp"

#include <unordered_map>

namespace cft
{
	struct ParticleRegistryEntry
	{
		int count;
		unsigned int poolId;
		unsigned int recursionDepth;
		float periodicTriggerAccumulator;
		std::optional<SpawnTriggerDescriptor> spawnTriggerDescriptor;
		RenderConfiguration renderConfiguration;
		std::vector<std::unique_ptr<ForceField>> forceFields;
		std::vector<std::unique_ptr<MotionBehavior>> motionBehaviors;
		std::vector<std::unique_ptr<VisualBehavior>> visualBehaviors;
	};

	class ParticleRegistry
	{
	private:
		std::unordered_map<unsigned int, ParticleRegistryEntry> m_entries;
		unsigned int m_nextId;

	public:
		ParticleRegistry();

		std::unordered_map<unsigned int, ParticleRegistryEntry>& getEntries();

		const ParticleRegistryEntry& getEntry(unsigned int id) const;
		ParticleRegistryEntry& getEntry(unsigned int id);

		void clear();

		unsigned int createEntry(unsigned int poolId, unsigned int recursionDepth, const std::optional<SpawnTriggerDescriptor>& spawnTriggerDescriptor, const RenderConfiguration& renderConfiguration, std::vector<std::unique_ptr<ForceField>> forceFields, std::vector<std::unique_ptr<MotionBehavior>>& motionBehaviors, std::vector<std::unique_ptr<VisualBehavior>>& visualBehaviors);
		void addReferenceCount(unsigned int id, int referenceCount);
	};
}