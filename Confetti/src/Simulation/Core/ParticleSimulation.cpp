#include "Confetti/Simulation/Core/ParticleSimulation.hpp"
#include "Confetti/Tool/Hasher.hpp"

namespace cft
{
	ParticleEmitterInstance ParticleSimulation::createParticleEmitter(const ParticleEmitterSpawnContext& emitterSpawnContext, const MotionState& parentMotionState, std::optional<std::uint64_t> parentSeed, unsigned int recursionDepth, float elapsedTime)
	{
		const ParticleEmitterDescriptor& particleEmitterDescriptor = m_assetRegistry.getParticleEmitterDescriptor(emitterSpawnContext.emitterDescriptorId);
		
		std::uint64_t emitterSeed = parentSeed.has_value() ? parentSeed.value() : m_seed;
		std::uint64_t emitterSpawnIndex = m_totalEmitterSpawnCount++;
		emitterSeed = Hasher::hash(emitterSeed, emitterSpawnIndex);

		std::vector<std::unique_ptr<ForceField>> forceFields = instantiateElements<ForceField>(emitterSeed, particleEmitterDescriptor.forceFieldIds, [this](unsigned int id) -> const ForceField& { return m_assetRegistry.getForceField(id); });
		std::vector<std::unique_ptr<MotionBehavior>> motionBehaviors = instantiateElements<MotionBehavior>(emitterSeed, particleEmitterDescriptor.motionBehaviorIds, [this](unsigned int id) -> const MotionBehavior& { return m_assetRegistry.getMotionBehavior(id); });
		std::vector<std::unique_ptr<VisualBehavior>> visualBehaviors = instantiateElements<VisualBehavior>(emitterSeed, particleEmitterDescriptor.visualBehaviorIds, [this](unsigned int id) -> const VisualBehavior& { return m_assetRegistry.getVisualBehavior(id); });

		ParticleEmitterInstance particleEmitterInstance;

		particleEmitterInstance.seed = emitterSeed;
		particleEmitterInstance.timeRange = emitterSpawnContext.timeRange;
		particleEmitterInstance.timeRange.spawnTime += elapsedTime;
		particleEmitterInstance.motionState = MotionState{ parentMotionState.position + emitterSpawnContext.initialMotionState.position, parentMotionState.linearVelocity + emitterSpawnContext.initialMotionState.linearVelocity, parentMotionState.rotation + emitterSpawnContext.initialMotionState.rotation, parentMotionState.angularVelocity + emitterSpawnContext.initialMotionState.angularVelocity };
		particleEmitterInstance.postBehaviorPosition = glm::vec3(0.0f);
		particleEmitterInstance.particleRegistryId = m_particleRegistry.createEntry(particleEmitterDescriptor.poolId, recursionDepth, emitterSeed, particleEmitterDescriptor.spawnTriggerDescriptor, particleEmitterDescriptor.renderConfiguration, std::move(forceFields), std::move(motionBehaviors), std::move(visualBehaviors));
		particleEmitterInstance.trailRegistryId = std::nullopt;
		if (particleEmitterDescriptor.trailConfiguration.has_value())
			particleEmitterInstance.trailRegistryId = std::make_optional<unsigned int>(m_trailRegistry.createEntry(particleEmitterDescriptor.trailConfiguration.value()));
		particleEmitterInstance.ribbonRegistryId = std::nullopt;
		if (particleEmitterDescriptor.ribbonConfiguration.has_value())
		{
			std::unique_ptr<ParticleLinker> particleLinker = instantiateElement<ParticleLinker>(emitterSeed, particleEmitterDescriptor.ribbonConfiguration.value().particleLinkerId, std::nullopt, [this](unsigned int id) -> const ParticleLinker& { return m_assetRegistry.getParticleLinker(id); });
			std::unique_ptr<RibbonGenerator> ribbonGenerator = instantiateElement<RibbonGenerator>(emitterSeed, particleEmitterDescriptor.ribbonConfiguration.value().ribbonGeneratorId, std::nullopt, [this](unsigned int id) -> const RibbonGenerator& { return m_assetRegistry.getRibbonGenerator(id); });
			particleEmitterInstance.ribbonRegistryId = std::make_optional<unsigned int>(m_ribbonRegistry.createEntry(particleEmitterDescriptor.poolId, particleEmitterDescriptor.ribbonConfiguration.value(), std::move(particleLinker), std::move(ribbonGenerator)));
		}

		particleEmitterInstance.particleSpawner = m_assetRegistry.getParticleSpawner(particleEmitterDescriptor.particleSpawnerId).clone();

		cft::ParticleSpawner::Seeds particleSpawnerSeeds = particleEmitterInstance.particleSpawner->getSeeds();
		std::uint64_t colorGeneratorSeed = calculateInstanceSeed(emitterSeed, particleEmitterDescriptor.particleSpawnerId, particleSpawnerSeeds.colorGeneratorSeed, 0);
		std::uint64_t positionGeneratorSeed = calculateInstanceSeed(emitterSeed, particleEmitterDescriptor.particleSpawnerId, particleSpawnerSeeds.positionGeneratorSeed, 1);
		std::uint64_t rotationGeneratorSeed = calculateInstanceSeed(emitterSeed, particleEmitterDescriptor.particleSpawnerId, particleSpawnerSeeds.rotationGeneratorSeed, 2);
		std::uint64_t scaleGeneratorSeed = calculateInstanceSeed(emitterSeed, particleEmitterDescriptor.particleSpawnerId, particleSpawnerSeeds.scaleGeneratorSeed, 3);
		std::uint64_t linearVelocityGeneratorSeed = calculateInstanceSeed(emitterSeed, particleEmitterDescriptor.particleSpawnerId, particleSpawnerSeeds.linearVelocityGeneratorSeed, 4);
		std::uint64_t angularVelocityGeneratorSeed = calculateInstanceSeed(emitterSeed, particleEmitterDescriptor.particleSpawnerId, particleSpawnerSeeds.angularVelocityGeneratorSeed, 5);
		std::uint64_t phaseGeneratorSeed = calculateInstanceSeed(emitterSeed, particleEmitterDescriptor.particleSpawnerId, particleSpawnerSeeds.phaseGeneratorSeed, 6);
		std::uint64_t lifetimeGeneratorSeed = calculateInstanceSeed(emitterSeed, particleEmitterDescriptor.particleSpawnerId, particleSpawnerSeeds.lifetimeGeneratorSeed, 7);
		particleEmitterInstance.particleSpawner->setSeeds(cft::ParticleSpawner::Seeds{ colorGeneratorSeed, positionGeneratorSeed, rotationGeneratorSeed, scaleGeneratorSeed, linearVelocityGeneratorSeed, angularVelocityGeneratorSeed, phaseGeneratorSeed, lifetimeGeneratorSeed });

		particleEmitterInstance.emissionPattern = instantiateElement<EmissionPattern>(emitterSeed, particleEmitterDescriptor.emissionPatternId, std::nullopt, [this](unsigned int id) -> const EmissionPattern& { return m_assetRegistry.getEmissionPattern(id); });
		particleEmitterInstance.motionStateInheritance = particleEmitterDescriptor.motionStateInheritance;
		particleEmitterInstance.inheritedForceFields = instantiateElements<ForceField>(emitterSeed, emitterSpawnContext.forceFieldIds, [this](unsigned int id) -> const ForceField& { return m_assetRegistry.getForceField(id); });
		particleEmitterInstance.inheritedMotionBehaviors = instantiateElements<MotionBehavior>(emitterSeed, emitterSpawnContext.motionBehaviorIds, [this](unsigned int id) -> const MotionBehavior& { return m_assetRegistry.getMotionBehavior(id); });

		unsigned int maximumParticleCount = particleEmitterInstance.emissionPattern->getMaximumSimultaneousParticleCount(particleEmitterInstance.particleSpawner->getMaxiumParticleLifetime());
		m_particlePools[particleEmitterDescriptor.poolId].reserveSlots(maximumParticleCount);
		if (particleEmitterDescriptor.trailConfiguration.has_value())
			m_trailPools[particleEmitterDescriptor.poolId].reserveSlots(maximumParticleCount);
		if (particleEmitterDescriptor.ribbonConfiguration.has_value())
			m_ribbonPools[particleEmitterDescriptor.poolId].reserveSlots(maximumParticleCount * (maximumParticleCount - 1) / 2);
		
		return particleEmitterInstance;
	}

	std::uint64_t ParticleSimulation::calculateInstanceSeed(std::uint64_t emitterSeed, unsigned int effectId, std::optional<std::uint64_t> baseSeed, std::optional<unsigned int> instanceIndex)
	{
		if (baseSeed.has_value())
		{
			if (instanceIndex.has_value())
				return Hasher::hash(emitterSeed, effectId, baseSeed.value(), instanceIndex.value());
			else
				return Hasher::hash(emitterSeed, effectId, baseSeed.value());
		}
		else
		{
			if (instanceIndex.has_value())
				return Hasher::hash(emitterSeed, effectId, instanceIndex.value());
			else
				return Hasher::hash(emitterSeed, effectId);
		}
	}

	ParticleSimulation::ParticleSimulation(AssetRegistry& assetRegistry) :
		m_assetRegistry(assetRegistry),
		m_seed(0),
		m_totalEmitterSpawnCount(0),
		m_particleEffectInstances(),
		m_particleEmitterInstances(),
		m_particlePools(),
		m_trailPools(),
		m_ribbonPools(),
		m_particleRegistry(),
		m_trailRegistry(),
		m_ribbonRegistry()
	{

	}

	const std::unordered_map<unsigned int, ParticlePool>& ParticleSimulation::getParticlePools() const
	{
		return m_particlePools;
	}

	const std::unordered_map<unsigned int, TrailPool>& ParticleSimulation::getTrailPools() const
	{
		return m_trailPools;
	}

	const std::unordered_map<unsigned int, RibbonPool>& ParticleSimulation::getRibbonPools() const
	{
		return m_ribbonPools;
	}

	const ParticleRegistry& ParticleSimulation::getParticleRegistry() const
	{
		return m_particleRegistry;
	}

	const TrailRegistry& ParticleSimulation::getTrailRegistry() const
	{
		return m_trailRegistry;
	}

	const RibbonRegistry& ParticleSimulation::getRibbonRegistry() const
	{
		return m_ribbonRegistry;
	}

	void ParticleSimulation::setSeed(std::uint64_t seed)
	{
		m_seed = seed;
	}

	void ParticleSimulation::addParticleEffect(unsigned int id, float elapsedTime)
	{
		m_particleEffectInstances.push_back(ParticleEffectInstance{ elapsedTime, m_assetRegistry.getParticleEffectDescriptor(id).emitterSpawnContexts });
	}

	void ParticleSimulation::clear()
	{
		m_totalEmitterSpawnCount = 0;

		m_particleEffectInstances.clear();
		m_particleEmitterInstances.clear();

		m_particlePools.clear();
		m_trailPools.clear();
		m_ribbonPools.clear();

		m_particleRegistry.clear();
		m_trailRegistry.clear();
		m_ribbonRegistry.clear();
	}

	void ParticleSimulation::update(float elapsedTime, float deltaTime)
	{		
		updateParticleEffects(elapsedTime, deltaTime);
		updateParticleEmitters(elapsedTime, deltaTime);
		updateParticles(elapsedTime, deltaTime);
		updateTrails(elapsedTime, deltaTime);
		updateRibbons(elapsedTime, deltaTime);
	}
}