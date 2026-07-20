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
		m_particlePools[particleEmitterDescriptor.poolId].reserve(maximumParticleCount);
		m_trailPools[particleEmitterDescriptor.poolId].reserve(maximumParticleCount);
		// Reserve correct amount for m_ribbonPools
		m_ribbonPools[particleEmitterDescriptor.poolId].reserve(maximumParticleCount * maximumParticleCount);
		
		return particleEmitterInstance;
	}

	void ParticleSimulation::updateTrail(std::deque<PathPoint>& trail, const PathConfiguration& pathConfiguration, const std::vector<glm::vec4>& colorGradient, float elapsedTime) const
	{
		unsigned int trailSize = static_cast<unsigned int>(trail.size());
		unsigned int colorGradientSize = static_cast<unsigned int>(colorGradient.size());

		for (unsigned int pointIndex = 0; pointIndex < trail.size(); ++pointIndex)
		{
			float t = 1.0f - (trailSize > 1 ? static_cast<float>(pointIndex) / static_cast<float>(trailSize - 1) : 0.0f);

			switch (pathConfiguration.thicknessDistribution)
			{
			case ThicknessDistribution::Linear: trail[pointIndex].thickness = glm::mix(pathConfiguration.startThickness, pathConfiguration.endThickness, t); break;
			case ThicknessDistribution::Quadratic: trail[pointIndex].thickness = glm::mix(pathConfiguration.startThickness, pathConfiguration.endThickness, t * t); break;
			}

			if (pathConfiguration.thicknessEvolution.has_value())
			{
				const ThicknessEvolution& trailThicknessEvolution = pathConfiguration.thicknessEvolution.value();
				float pointAge = (elapsedTime - trail[pointIndex].spawnTime);

				switch (trailThicknessEvolution.distribution)
				{
				case ThicknessEvolutionDistribution::Constant: trail[pointIndex].thickness += pointAge * trailThicknessEvolution.speed; break;
				case ThicknessEvolutionDistribution::Linear: trail[pointIndex].thickness += t * pointAge * trailThicknessEvolution.speed; break;
				case ThicknessEvolutionDistribution::Quadratic: trail[pointIndex].thickness += t * t * pointAge * trailThicknessEvolution.speed; break;
				}

				trail[pointIndex].thickness = glm::max(trail[pointIndex].thickness, 0.0f);
			}

			switch (pathConfiguration.colorInterpolation)
			{
			case ColorInterpolation::Constant:
			{
				if (pathConfiguration.colorStart.has_value())
				{
					const std::vector<float>& colorStart = pathConfiguration.colorStart.value();
					float distanceFromHead = trail.back().distanceOnTrail - trail[pointIndex].distanceOnTrail;

					size_t count = std::min(colorGradient.size(), colorStart.size());
					unsigned int colorIndex = colorGradientSize - 1;
					for (unsigned int j = 0; j < count; ++j)
					{
						if (distanceFromHead <= colorStart[j])
						{
							colorIndex = j;
							break;
						}
					}

					trail[pointIndex].color = colorGradient[colorIndex];
				}
				else
				{
					unsigned int colorIndex = glm::min(static_cast<unsigned int>(t * colorGradientSize), colorGradientSize - 1);
					trail[pointIndex].color = colorGradient[colorIndex];
				}
				break;
			}
			case ColorInterpolation::Linear:
			{
				if (pathConfiguration.colorStart.has_value())
				{
					const std::vector<float>& colorStart = pathConfiguration.colorStart.value();
					float distanceFromHead = trail.back().distanceOnTrail - trail[pointIndex].distanceOnTrail;

					size_t intervalCount = std::min(colorStart.size(), colorGradient.size() > 0 ? colorGradient.size() - 1 : 0);
					if (intervalCount == 0)
						break;

					if (distanceFromHead >= colorStart.back())
					{
						trail[pointIndex].color = colorGradient.back();
					}
					else
					{
						for (size_t j = 0; j < intervalCount; ++j)
						{
							float start = (j == 0) ? 0.0f : colorStart[j - 1];
							float end = colorStart[j];

							if (distanceFromHead <= end)
							{
								float t = (distanceFromHead - start) / (end - start);
								t = glm::clamp(t, 0.0f, 1.0f);

								trail[pointIndex].color = glm::mix(colorGradient[j], colorGradient[j + 1], t);

								break;
							}
						}
					}
				}
				else
				{
					float integralPart;
					float colorT = std::modf(t * static_cast<float>(colorGradientSize - 1), &integralPart);

					unsigned int colorIndexA = static_cast<unsigned int>(integralPart);
					unsigned int colorIndexB = glm::min(colorIndexA + 1, colorGradientSize - 1);
					trail[pointIndex].color = glm::mix(colorGradient[colorIndexA], colorGradient[colorIndexB], colorT);
				}
				break;
			}
			}

			if (pathConfiguration.lifetimeFade.has_value())
			{
				float start = pathConfiguration.lifetimeFade.value().start;
				float end = pathConfiguration.lifetimeFade.value().end;

				float age = elapsedTime - trail[pointIndex].spawnTime;
				float trailFadeT = end > start ? (glm::clamp(age, start, end) - start) / (end - start) : 1.0f;

				trail[pointIndex].color.a *= 1.0f - trailFadeT;
			}
		}

		if (pathConfiguration.lifetime.has_value())
		{
			while (!trail.empty() && elapsedTime >= trail.front().spawnTime + pathConfiguration.lifetime.value())
				trail.pop_front();
		}
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
		// Particle effects update
		for (unsigned int i = 0; i < m_particleEffectInstances.size();)
		{
			ParticleEffectInstance& particleEffectInstance = m_particleEffectInstances[i];

			for (unsigned int j = 0; j < particleEffectInstance.emitterSpawnContexts.size();)
			{
				const ParticleEmitterSpawnContext& emitterSpawnContext = particleEffectInstance.emitterSpawnContexts[j];
				if (elapsedTime >= particleEffectInstance.spawnTime + emitterSpawnContext.timeRange.spawnTime)
				{
					ParticleEmitterInstance particleEmitterInstance = createParticleEmitter(emitterSpawnContext, MotionState{}, 0, elapsedTime);

					m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, 1);

					if (particleEmitterInstance.trailRegistryId.has_value())
						m_trailRegistry.addReferenceCount(particleEmitterInstance.trailRegistryId.value(), 1);

					if (particleEmitterInstance.ribbonRegistryId.has_value())
						m_ribbonRegistry.addReferenceCount(particleEmitterInstance.ribbonRegistryId.value(), 1);

					m_particleEmitterInstances.push_back(std::move(particleEmitterInstance));

					particleEffectInstance.emitterSpawnContexts[j] = std::move(particleEffectInstance.emitterSpawnContexts.back());
					particleEffectInstance.emitterSpawnContexts.pop_back();
				}
				else
				{
					++j;
				}
			}

			if (particleEffectInstance.emitterSpawnContexts.empty())
			{
				m_particleEffectInstances[i] = std::move(m_particleEffectInstances.back());
				m_particleEffectInstances.pop_back();
			}
			else
			{
				++i;
			}
		}

		std::vector<ParticleEmitterInstance> pendingParticleEmitterInstances;

		// Particle emitters update
		for (unsigned int i = 0; i < m_particleEmitterInstances.size();)
		{
			ParticleEmitterInstance& particleEmitterInstance = m_particleEmitterInstances[i];

			float despawnTime = particleEmitterInstance.timeRange.spawnTime + particleEmitterInstance.timeRange.duration;
			if (elapsedTime >= despawnTime)
			{
				m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, -1);

				if (particleEmitterInstance.trailRegistryId.has_value())
					m_trailRegistry.addReferenceCount(particleEmitterInstance.trailRegistryId.value(), -1);

				if (particleEmitterInstance.ribbonRegistryId.has_value())
					m_ribbonRegistry.addReferenceCount(particleEmitterInstance.ribbonRegistryId.value(), -1);

				m_particleEmitterInstances[i] = std::move(m_particleEmitterInstances.back());
				m_particleEmitterInstances.pop_back();
			}
			else
			{
				for (const std::unique_ptr<ForceField>& forceField : particleEmitterInstance.inheritedForceFields)
				{
					MotionAcceleration motionAcceleration = forceField->evaluate(particleEmitterInstance.motionState);

					particleEmitterInstance.motionState.linearVelocity += motionAcceleration.linear * deltaTime;
					particleEmitterInstance.motionState.angularVelocity += motionAcceleration.angular * deltaTime;
				}

				particleEmitterInstance.motionState.position += particleEmitterInstance.motionState.linearVelocity * deltaTime;
				particleEmitterInstance.motionState.rotation = glm::normalize(glm::quat(1.0f, 0.5f * particleEmitterInstance.motionState.angularVelocity * deltaTime) * particleEmitterInstance.motionState.rotation);

				particleEmitterInstance.postBehaviorPosition = particleEmitterInstance.motionState.position;

				for (const std::unique_ptr<MotionBehavior>& motionBehavior : particleEmitterInstance.inheritedMotionBehaviors)
					particleEmitterInstance.postBehaviorPosition += motionBehavior->evaluate(elapsedTime - particleEmitterInstance.timeRange.spawnTime, particleEmitterInstance.motionState);

				unsigned int particleSpawnCount = particleEmitterInstance.emissionPattern->emit(deltaTime);
				if (particleSpawnCount > 0)
				{
					std::vector<Particle> particles = particleEmitterInstance.particleSpawner->spawn(particleSpawnCount, elapsedTime, deltaTime, particleEmitterInstance.particleRegistryId);
					
					const ParticleRegistryEntry& particleRegistryEntry = m_particleRegistry.getEntry(particleEmitterInstance.particleRegistryId);
					ParticlePool& particlePool = m_particlePools.at(particleRegistryEntry.poolId);
					particlePool.reserve(particleSpawnCount);

					bool spawnSpawnTrigger = false;
					ParticleEmitterSpawnContext spawnParticleEmitterSpawnContext;
					if (particleRegistryEntry.spawnTriggerDescriptor.has_value())
					{
						const SpawnTriggerDescriptor& spawnTriggerDescriptorValue = particleRegistryEntry.spawnTriggerDescriptor.value();
						spawnSpawnTrigger = particleRegistryEntry.recursionDepth < spawnTriggerDescriptorValue.maximumRecursionDepth && spawnTriggerDescriptorValue.spawnEmitterSpawnContext.has_value();
						if (spawnSpawnTrigger)
							spawnParticleEmitterSpawnContext = spawnTriggerDescriptorValue.spawnEmitterSpawnContext.value();
					}

					bool spawnTrails = particleEmitterInstance.trailRegistryId.has_value();
					std::optional<TrailPool*> trailPool;
					if (spawnTrails)
					{
						trailPool = &m_trailPools.at(particleRegistryEntry.poolId);
						trailPool.value()->reserve(particleSpawnCount);
					}						

					for (Particle& particle : particles)
					{
						particle.position += particleEmitterInstance.postBehaviorPosition;
						particle.linearVelocity += particleEmitterInstance.motionState.linearVelocity;
						particlePool.insert(particle);

						if (spawnTrails)
							trailPool.value()->insert(Trail{ particleEmitterInstance.trailRegistryId.value(), particle.id, -1.0f, particle.color, {} });

						if (spawnSpawnTrigger)
						{
							ParticleEmitterInstance spawnParticleEmitterInstance = createParticleEmitter(spawnParticleEmitterSpawnContext, MotionState{ particle.position, particle.linearVelocity, particle.rotation, particle.angularVelocity }, particleRegistryEntry.recursionDepth + 1, elapsedTime);
							pendingParticleEmitterInstances.push_back(std::move(spawnParticleEmitterInstance));
						}
					}

					m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, particleSpawnCount);
					if (spawnTrails)
						m_trailRegistry.addReferenceCount(particleEmitterInstance.trailRegistryId.value(), particleSpawnCount);
				}

				++i;
			}
		}

		for (ParticleEmitterInstance& particleEmitterInstance : pendingParticleEmitterInstances)
		{
			m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, 1);
			if (particleEmitterInstance.trailRegistryId.has_value())
				m_trailRegistry.addReferenceCount(particleEmitterInstance.trailRegistryId.value(), 1);

			m_particleEmitterInstances.push_back(std::move(particleEmitterInstance));
		}

		std::unordered_set<unsigned int> triggeredPeriodicSpawnTriggers;

		for (auto& [id, entry] : m_particleRegistry.getEntries())
		{
			if (entry.spawnTriggerDescriptor.has_value() && entry.spawnTriggerDescriptor.value().periodicEmitterSpawnContext.has_value())
			{
				SpawnTriggerDescriptor& spawnTriggerDescriptor = entry.spawnTriggerDescriptor.value();
				if (spawnTriggerDescriptor.periodicEmitterSpawnContext.has_value())
				{
					PeriodicSpawnTriggerContext& periodicSpawnTriggerContext = spawnTriggerDescriptor.periodicEmitterSpawnContext.value();
					entry.periodicTriggerAccumulator += deltaTime;

					if (entry.recursionDepth < spawnTriggerDescriptor.maximumRecursionDepth && entry.periodicTriggerAccumulator >= periodicSpawnTriggerContext.interval)
					{
						triggeredPeriodicSpawnTriggers.insert(id);
						entry.periodicTriggerAccumulator -= periodicSpawnTriggerContext.interval;
					}
				}
			}
		}

		// Particles update
		for (auto& [poolId, particlePool] : m_particlePools)
		{
			std::vector<glm::vec4>& color = particlePool.getColor();
			std::vector<glm::vec3>& position = particlePool.getPosition();
			std::vector<glm::quat>& rotation = particlePool.getRotation();
			std::vector<glm::vec3>& scale = particlePool.getScale();
			std::vector<glm::vec3>& linearVelocity = particlePool.getLinearVelocity();
			std::vector<glm::vec3>& angularVelocity = particlePool.getAngularVelocity();
			const std::vector<glm::vec4>& initialColor = particlePool.getInitialColor();
			const std::vector<glm::vec3>& initialScale = particlePool.getInitialScale();
			std::vector<glm::vec3>& postBehaviorPosition = particlePool.getPostBehaviorPosition();
			const std::vector<float>& phase = particlePool.getPhase();
			const std::vector<float>& lifetime = particlePool.getLifetime();
			const std::vector<float>& spawnTime = particlePool.getSpawnTime();
			const std::vector<unsigned int>& id = particlePool.getId();
			const std::vector<unsigned int>& particleRegistryId = particlePool.getParticleRegistryId();

			std::unordered_map<unsigned int, unsigned int> removedParticleCount;

			for (unsigned int i = 0; i < particlePool.getCount();)
			{
				ParticleRegistryEntry& entry = m_particleRegistry.getEntry(particleRegistryId[i]);

				float despawnTime = spawnTime[i] + lifetime[i];
				if (elapsedTime >= despawnTime)
				{				
					if (entry.spawnTriggerDescriptor.has_value())
					{
						const SpawnTriggerDescriptor& spawnTriggerValue = entry.spawnTriggerDescriptor.value();
						if (entry.recursionDepth < spawnTriggerValue.maximumRecursionDepth && spawnTriggerValue.deathEmitterSpawnContext.has_value())
						{
							ParticleEmitterInstance deathParticleEmitterInstance = createParticleEmitter(spawnTriggerValue.deathEmitterSpawnContext.value(), MotionState{ position[i], linearVelocity[i], rotation[i], angularVelocity[i] }, entry.recursionDepth + 1, elapsedTime);
							m_particleRegistry.addReferenceCount(deathParticleEmitterInstance.particleRegistryId, 1);
							if (deathParticleEmitterInstance.trailRegistryId.has_value())
								m_trailRegistry.addReferenceCount(deathParticleEmitterInstance.trailRegistryId.value(), 1);
							m_particleEmitterInstances.push_back(std::move(deathParticleEmitterInstance));
						}
					}

					++removedParticleCount[particleRegistryId[i]];
					particlePool.remove(i);
				}
				else
				{
					if (triggeredPeriodicSpawnTriggers.find(particleRegistryId[i]) != triggeredPeriodicSpawnTriggers.end())
					{
						ParticleEmitterInstance periodicParticleEmitterInstance = createParticleEmitter(entry.spawnTriggerDescriptor.value().periodicEmitterSpawnContext.value().emitterSpawnContext, MotionState{ position[i], linearVelocity[i], rotation[i], angularVelocity[i] }, entry.recursionDepth + 1, elapsedTime);
						m_particleRegistry.addReferenceCount(periodicParticleEmitterInstance.particleRegistryId, 1);
						if (periodicParticleEmitterInstance.trailRegistryId.has_value())
							m_trailRegistry.addReferenceCount(periodicParticleEmitterInstance.trailRegistryId.value(), 1);
						m_particleEmitterInstances.push_back(std::move(periodicParticleEmitterInstance));
					}

					MotionState motionState{ position[i], linearVelocity[i], rotation[i], angularVelocity[i] };
					for (const std::unique_ptr<ForceField>& forceField : entry.forceFields)
					{
						MotionAcceleration motionAcceleration = forceField->evaluate(motionState);

						motionState.linearVelocity += motionAcceleration.linear * deltaTime;
						motionState.angularVelocity += motionAcceleration.angular * deltaTime;
					}

					motionState.position += motionState.linearVelocity * deltaTime;
					motionState.rotation = glm::normalize(glm::quat(1.0f, 0.5f * motionState.angularVelocity * deltaTime) * motionState.rotation);

					position[i] = motionState.position;
					rotation[i] = motionState.rotation;
					linearVelocity[i] = motionState.linearVelocity;
					angularVelocity[i] = motionState.angularVelocity;

					postBehaviorPosition[i] = motionState.position;

					float particleAge = elapsedTime - spawnTime[i];

					for (const std::unique_ptr<MotionBehavior>& motionBehavior : entry.motionBehaviors)
						postBehaviorPosition[i] += motionBehavior->evaluate(particleAge, motionState);

					float particleNormalizedAge = particleAge / lifetime[i];

					for (const std::unique_ptr<VisualBehavior>& visualBehavior : entry.visualBehaviors)
						visualBehavior->evaluate(elapsedTime, particleNormalizedAge, ParticleView{ color[i], position[i], rotation[i], scale[i], linearVelocity[i], angularVelocity[i], initialColor[i], initialScale[i], postBehaviorPosition[i], phase[i], lifetime[i], spawnTime[i], particleRegistryId[i], id[i] });

					++i;
				}
			}

			for (auto& [particleRegistry, count] : removedParticleCount)
				m_particleRegistry.addReferenceCount(particleRegistry, -static_cast<int>(count));
		}

		// Trails update
		for (auto& [poolId, trailPool] : m_trailPools)
		{
			const std::vector<unsigned int>& trailRegistryId = trailPool.getTrailRegistryId();
			const std::vector<unsigned int>& particleId = trailPool.getParticleId();
			std::vector<float>& particleDeathTime = trailPool.getParticleDeathTime();
			std::vector<glm::vec4>& particleColor = trailPool.getParticleColor();
			std::vector<std::deque<PathPoint>>& trailPoints = trailPool.getPathPoints();

			std::unordered_map<unsigned int, unsigned int> removedTrailCount;

			for (unsigned int i = 0; i < trailPool.getCount();)
			{
				TrailRegistryEntry& trailRegistryEntry = m_trailRegistry.getEntry(trailRegistryId[i]);

				if (particleDeathTime[i] < 0.0f)
				{
					const ParticlePool& particlePool = m_particlePools.at(poolId);

					std::optional<unsigned int> ownerParticleIndex = particlePool.getIndex(particleId[i]);
					if (!ownerParticleIndex.has_value())
					{
						particleDeathTime[i] = elapsedTime;
					}
					else
					{
						particleColor[i] = particlePool.getColor()[ownerParticleIndex.value()];
						glm::vec3 particlePosition = particlePool.getPostBehaviorPosition()[ownerParticleIndex.value()];
						if (trailPoints[i].empty() || glm::distance(particlePosition, trailPoints[i].back().position) > trailRegistryEntry.trailConfiguration.minimumSpawnDistance || (trailRegistryEntry.trailConfiguration.maximumSpawnTime.has_value() && elapsedTime - trailPoints[i].back().spawnTime > trailRegistryEntry.trailConfiguration.maximumSpawnTime.value()))
						{
							float distanceOnTrail = 0.0f;
							if (!trailPoints[i].empty())
								distanceOnTrail = trailPoints[i].back().distanceOnTrail + glm::distance(trailPoints[i].back().position, particlePosition);

							trailPoints[i].push_back(PathPoint{ glm::vec4(1.0f), particlePosition, 1.0f, distanceOnTrail, elapsedTime });

							if (trailRegistryEntry.trailConfiguration.maximumSegmentCount.has_value() && trailPoints[i].size() > trailRegistryEntry.trailConfiguration.maximumSegmentCount.value())
							{
								while (trailPoints[i].size() > trailRegistryEntry.trailConfiguration.maximumSegmentCount.value())
									trailPoints[i].pop_front();
							}
						}
					}
				}

				if (particleDeathTime[i] >= 0.0f && elapsedTime >= trailRegistryEntry.trailConfiguration.presistenceLifetime + particleDeathTime[i])
				{
					++removedTrailCount[trailRegistryId[i]];
					trailPool.remove(i);
				}
				else
				{
					unsigned int colorGradientSize = static_cast<unsigned int>(trailRegistryEntry.trailConfiguration.pathConfiguration.colorGradient.size()) + (trailRegistryEntry.trailConfiguration.pathConfiguration.appendParticleColor ? 1 : 0);
					std::vector<glm::vec4> colorGradient;
					colorGradient.reserve(colorGradientSize);
					if (trailRegistryEntry.trailConfiguration.pathConfiguration.appendParticleColor)
						colorGradient.push_back(particleColor[i]);
					colorGradient.insert(colorGradient.end(), trailRegistryEntry.trailConfiguration.pathConfiguration.colorGradient.begin(), trailRegistryEntry.trailConfiguration.pathConfiguration.colorGradient.end());
					
					updateTrail(trailPoints[i], trailRegistryEntry.trailConfiguration.pathConfiguration, colorGradient, elapsedTime);

					++i;
				}
			}

			for (auto& [trailRegistry, count] : removedTrailCount)
				m_trailRegistry.addReferenceCount(trailRegistry, -static_cast<int>(count));
		}

		// Ribbons update
		for (auto& [ribbonRegistryId, ribbonRegistryEntry] : m_ribbonRegistry.getEntries())
		{
			unsigned int createdRibbonsCount = ribbonRegistryEntry.particleConnector->createRibbons(m_ribbonPools[ribbonRegistryEntry.poolId], m_particlePools[ribbonRegistryEntry.poolId], ribbonRegistryId, elapsedTime);
			m_ribbonRegistry.addReferenceCount(ribbonRegistryId, createdRibbonsCount);
		}

		for (auto& [poolId, ribbonPool] : m_ribbonPools)
		{
			const std::vector<unsigned int>& ribbonRegistryId = ribbonPool.getRibbonRegistryId();
			const std::vector<unsigned int>& fromParticleId = ribbonPool.getFromParticleId();
			const std::vector<unsigned int>& toParticleId = ribbonPool.getToParticleId();
			const std::vector<float>& spawnTime = ribbonPool.getSpawnTime();
			std::vector<std::deque<PathPoint>>& ribbonPoints = ribbonPool.getRibbonPoints();

			std::unordered_map<unsigned int, unsigned int> removedRibbonCount;

			for (unsigned int i = 0; i < ribbonPool.getCount();)
			{
				RibbonRegistryEntry& ribbonRegistryEntry = m_ribbonRegistry.getEntry(ribbonRegistryId[i]);
				const ParticlePool& particlePool = m_particlePools[ribbonRegistryEntry.poolId];

				const std::vector<glm::vec4>& particleColor = particlePool.getColor();
				const std::vector<glm::vec3>& particlePosition = particlePool.getPosition();
				const std::vector<glm::quat>& particleRotation = particlePool.getRotation();
				const std::vector<glm::vec3>& particleScale = particlePool.getScale();
				const std::vector<glm::vec3>& particleLinearVelocity = particlePool.getLinearVelocity();
				const std::vector<glm::vec3>& particleAngularVelocity = particlePool.getAngularVelocity();
				const std::vector<glm::vec4>& particleInitialColor = particlePool.getInitialColor();
				const std::vector<glm::vec3>& particleInitialScale = particlePool.getInitialScale();
				const std::vector<glm::vec3>& particlePostBehaviorPosition = particlePool.getPostBehaviorPosition();
				const std::vector<float>& particlePhase = particlePool.getPhase();
				const std::vector<float>& particleLifetime = particlePool.getLifetime();
				const std::vector<float>& particleSpawnTime = particlePool.getSpawnTime();
				const std::vector<unsigned int>& particleId = particlePool.getId();
				const std::vector<unsigned int>& particleParticleRegistryId = particlePool.getParticleRegistryId();

				std::optional<unsigned int> fromParticleIndex = particlePool.getIndex(fromParticleId[i]);
				std::optional<unsigned int> toParticleIndex = particlePool.getIndex(toParticleId[i]);

				if (!fromParticleIndex.has_value() || !toParticleIndex.has_value() || (ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.lifetime.has_value() && (elapsedTime - spawnTime[i]) > ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.lifetime.value()))
				{
					ribbonPool.remove(i);
					++removedRibbonCount[ribbonRegistryId[i]];
				}
				else
				{
					unsigned int fromParticleIndexValue = fromParticleIndex.value();
					unsigned int toParticleIndexValue = toParticleIndex.value();

					ConstantParticleView fromParticle{ particleColor[fromParticleIndexValue], particlePosition[fromParticleIndexValue], particleRotation[fromParticleIndexValue], particleScale[fromParticleIndexValue], particleLinearVelocity[fromParticleIndexValue], particleAngularVelocity[fromParticleIndexValue], particleInitialColor[fromParticleIndexValue], particleInitialScale[fromParticleIndexValue], particlePostBehaviorPosition[fromParticleIndexValue], particlePhase[fromParticleIndexValue], particleLifetime[fromParticleIndexValue], particleSpawnTime[fromParticleIndexValue], particleParticleRegistryId[fromParticleIndexValue], particleId[fromParticleIndexValue] };
					ConstantParticleView toParticle{ particleColor[toParticleIndexValue], particlePosition[toParticleIndexValue], particleRotation[toParticleIndexValue], particleScale[toParticleIndexValue], particleLinearVelocity[toParticleIndexValue], particleAngularVelocity[toParticleIndexValue], particleInitialColor[toParticleIndexValue], particleInitialScale[toParticleIndexValue], particlePostBehaviorPosition[toParticleIndexValue], particlePhase[toParticleIndexValue], particleLifetime[toParticleIndexValue], particleSpawnTime[toParticleIndexValue], particleParticleRegistryId[toParticleIndexValue], particleId[toParticleIndexValue] };

					if (ribbonRegistryEntry.particleConnector->isRibbonValid(fromParticle, toParticle))
					{
						unsigned int colorGradientSize = static_cast<unsigned int>(ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.colorGradient.size()) + (ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.appendParticleColor ? 2 : 0);
						std::vector<glm::vec4> colorGradient;
						colorGradient.reserve(colorGradientSize);
						if (ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.appendParticleColor)
							colorGradient.push_back(fromParticle.color);
						colorGradient.insert(colorGradient.end(), ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.colorGradient.begin(), ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.colorGradient.end());
						if (ribbonRegistryEntry.ribbonConfiguration.pathConfiguration.appendParticleColor)
							colorGradient.push_back(toParticle.color);

						ribbonRegistryEntry.particleConnector->updateRibbon(RibbonView{ ribbonRegistryId[i], fromParticleId[i], toParticleId[i], spawnTime[i], ribbonPoints[i] }, ribbonRegistryEntry.ribbonConfiguration.pathConfiguration, fromParticle, toParticle);
						updateTrail(ribbonPoints[i], ribbonRegistryEntry.ribbonConfiguration.pathConfiguration, colorGradient, elapsedTime);

						++i;
					}
					else
					{
						ribbonPool.remove(i);
						++removedRibbonCount[ribbonRegistryId[i]];
					}
				}
			}

			for (auto& [ribbonRegistry, count] : removedRibbonCount)
				m_ribbonRegistry.addReferenceCount(ribbonRegistry, -static_cast<int>(count));
		}
	}
}