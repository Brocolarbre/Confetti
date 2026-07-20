#include "Confetti/Simulation/Core/ParticleSimulation.hpp"

namespace cft
{
	ParticleEmitterInstance ParticleSimulation::createParticleEmitter(const ParticleEmitterSpawnContext& emitterSpawnContext, const MotionState& parentMotionState, unsigned int recursionDepth, float elapsedTime)
	{
		const ParticleEmitterDescriptor& particleEmitterDescriptor = m_assetRegistry.getParticleEmitterDescriptor(emitterSpawnContext.emitterDescriptorId);
		
		std::vector<std::unique_ptr<ForceField>> forceFields;
		forceFields.reserve(particleEmitterDescriptor.forceFieldIds.size());
		for (unsigned int forceFieldId : particleEmitterDescriptor.forceFieldIds)
			forceFields.push_back(m_assetRegistry.getForceField(forceFieldId).clone());

		std::vector<std::unique_ptr<MotionBehavior>> motionBehaviors;
		motionBehaviors.reserve(particleEmitterDescriptor.motionBehaviorIds.size());
		for (unsigned int motionBehaviorId : particleEmitterDescriptor.motionBehaviorIds)
			motionBehaviors.push_back(m_assetRegistry.getMotionBehavior(motionBehaviorId).clone());

		std::vector<std::unique_ptr<VisualBehavior>> visualBehaviors;
		visualBehaviors.reserve(particleEmitterDescriptor.visualBehaviorIds.size());
		for (unsigned int visualBehaviorId : particleEmitterDescriptor.visualBehaviorIds)
			visualBehaviors.push_back(m_assetRegistry.getVisualBehavior(visualBehaviorId).clone());

		ParticleEmitterInstance particleEmitterInstance;

		particleEmitterInstance.timeRange = emitterSpawnContext.timeRange;
		particleEmitterInstance.timeRange.spawnTime += elapsedTime;
		particleEmitterInstance.motionState = MotionState{ parentMotionState.position + emitterSpawnContext.initialMotionState.position, parentMotionState.linearVelocity + emitterSpawnContext.initialMotionState.linearVelocity, parentMotionState.rotation + emitterSpawnContext.initialMotionState.rotation, parentMotionState.angularVelocity + emitterSpawnContext.initialMotionState.angularVelocity };
		particleEmitterInstance.postBehaviorPosition = glm::vec3(0.0f);
		particleEmitterInstance.particleRegistryId = m_particleRegistry.createEntry(particleEmitterDescriptor.poolId, recursionDepth, particleEmitterDescriptor.spawnTriggerDescriptor, particleEmitterDescriptor.renderConfiguration, std::move(forceFields), std::move(motionBehaviors), std::move(visualBehaviors));
		particleEmitterInstance.trailRegistryId = particleEmitterDescriptor.trailConfiguration.has_value() ? std::make_optional<unsigned int>(m_trailRegistry.createEntry(particleEmitterDescriptor.trailConfiguration.value())) : std::nullopt;
		particleEmitterInstance.ribbonRegistryId = particleEmitterDescriptor.ribbonConfiguration.has_value() ? std::make_optional<unsigned int>(m_ribbonRegistry.createEntry(particleEmitterDescriptor.poolId, particleEmitterDescriptor.ribbonConfiguration.value(), m_assetRegistry.getParticleLinker(particleEmitterDescriptor.ribbonConfiguration.value().particleConnectorId).clone())) : std::nullopt;
		particleEmitterInstance.particleSpawner = m_assetRegistry.getParticleSpawner(particleEmitterDescriptor.particleSpawnerId).clone();
		particleEmitterInstance.emissionPattern = m_assetRegistry.getEmissionPattern(particleEmitterDescriptor.emissionPatternId).clone();

		particleEmitterInstance.inheritedForceFields.reserve(emitterSpawnContext.forceFieldIds.size());
		for (unsigned int forceFieldId : emitterSpawnContext.forceFieldIds)
			particleEmitterInstance.inheritedForceFields.push_back(m_assetRegistry.getForceField(forceFieldId).clone());

		particleEmitterInstance.inheritedMotionBehaviors.reserve(emitterSpawnContext.motionBehaviorIds.size());
		for (unsigned int motionBehaviorId : emitterSpawnContext.motionBehaviorIds)
			particleEmitterInstance.inheritedMotionBehaviors.push_back(m_assetRegistry.getMotionBehavior(motionBehaviorId).clone());

		unsigned int maximumParticleCount = particleEmitterInstance.emissionPattern->getMaximumSimultaneousParticleCount(particleEmitterInstance.particleSpawner->getMaxiumParticleLifetime());
		m_particlePools[particleEmitterDescriptor.poolId].reserveSlots(maximumParticleCount);
		if (particleEmitterDescriptor.trailConfiguration.has_value())
			m_trailPools[particleEmitterDescriptor.poolId].reserveSlots(maximumParticleCount);
		if (particleEmitterDescriptor.ribbonConfiguration.has_value())
			m_ribbonPools[particleEmitterDescriptor.poolId].reserveSlots(m_assetRegistry.getParticleLinker(particleEmitterDescriptor.ribbonConfiguration.value().particleConnectorId).getMaximumRibbonCount(maximumParticleCount));
		
		return particleEmitterInstance;
	}

	ParticleSimulation::ParticleSimulation(AssetRegistry& assetRegistry, RandomNumberGenerator& randomNumberGenerator) :
		m_assetRegistry(assetRegistry),
		m_randomNumberGenerator(randomNumberGenerator),
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

	void ParticleSimulation::addParticleEffect(float elapsedTime, unsigned int id)
	{
		m_particleEffectInstances.push_back(ParticleEffectInstance{ elapsedTime, m_assetRegistry.getParticleEffectDescriptor(id).emitterSpawnContexts });
	}

	void ParticleSimulation::clear()
	{
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