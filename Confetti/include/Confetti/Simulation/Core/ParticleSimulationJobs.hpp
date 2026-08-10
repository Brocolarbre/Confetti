#pragma once

#include "ParticleEmitterInstance.hpp"

namespace cft
{
    struct ParticleEmitterSpawnRequest
    {
        unsigned int sourceParticleId;
        ParticleEmitterSpawnContext spawnContext;
        MotionState motionState;
        std::optional<uint64_t> parentSeed;
        unsigned int recursionDepth;
    };

    struct ParticleRemoval
    {
        unsigned int poolId;
        unsigned int particleIndex;
        unsigned int particleRegistryId;
    };

    struct ParticleUpdateResult
    {
        std::vector<ParticleEmitterSpawnRequest> emitterSpawnRequests;
        std::vector<ParticleRemoval> removedParticles;
    };

    struct TrailRemoval
    {
        unsigned int poolId;
        unsigned int trailIndex;
        unsigned int trailRegistryId;
    };

    struct TrailUpdateResult
    {
        std::vector<TrailRemoval> removedTrails;
    };

    struct RibbonRemoval
    {
        unsigned int poolId;
        unsigned int ribbonIndex;
        unsigned int ribbonRegistryId;
    };

    struct RibbonUpdateResult
    {
        std::vector<RibbonRemoval> removedRibbons;
    };
}