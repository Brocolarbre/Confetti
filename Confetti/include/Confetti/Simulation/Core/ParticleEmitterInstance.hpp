#pragma once

#include "Confetti/Data/ParticleEmitterDescriptor.hpp"
#include "Confetti/Emission/ParticleSpawner.hpp"
#include "Confetti/Emission/EmissionPattern/EmissionPattern.hpp"
#include "Confetti/Behavior/Force/ForceField.hpp"
#include "Confetti/Behavior/Motion/MotionBehavior.hpp"

namespace cft
{
	struct ParticleEmitterInstance
	{
		TimeRange timeRange;
		MotionState motionState;
		glm::vec3 postBehaviorPosition;
		unsigned int particleRegistryId;
		std::optional<unsigned int> trailRegistryId;
		std::optional<unsigned int> ribbonRegistryId;
		std::unique_ptr<ParticleSpawner> particleSpawner;
		std::unique_ptr<EmissionPattern> emissionPattern;
		std::vector<std::unique_ptr<ForceField>> inheritedForceFields;
		std::vector<std::unique_ptr<MotionBehavior>> inheritedMotionBehaviors;
	};
}