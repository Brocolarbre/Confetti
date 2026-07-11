#include "Confetti/ParticleSimulation/ParticleSimulation.hpp"

#include <unordered_set>

namespace cft
{
	ParticleEmitterInstance ParticleSimulation::createParticleEmitter(const ParticleEmitterDescriptor& descriptor, const MotionState& parentMotionState, unsigned int recursionDepth, float elapsedTime)
	{
		const ParticleEmitter& particleEmitter = m_assetRegistry.getParticleEmitter(descriptor.emitterId);

		std::vector<std::unique_ptr<ForceField>> forceFields;
		forceFields.reserve(particleEmitter.forceFieldIds.size());
		for (unsigned int forceFieldId : particleEmitter.forceFieldIds)
			forceFields.push_back(m_assetRegistry.getForceField(forceFieldId).clone());

		std::vector<std::unique_ptr<MotionBehavior>> motionBehaviors;
		motionBehaviors.reserve(particleEmitter.motionBehaviorIds.size());
		for (unsigned int motionBehaviorId : particleEmitter.motionBehaviorIds)
			motionBehaviors.push_back(m_assetRegistry.getMotionBehavior(motionBehaviorId).clone());

		std::vector<std::unique_ptr<ParticleBehavior>> particleBehaviors;
		particleBehaviors.reserve(particleEmitter.particleBehaviorIds.size());
		for (unsigned int particleBehaviorId : particleEmitter.particleBehaviorIds)
			particleBehaviors.push_back(m_assetRegistry.getParticleBehavior(particleBehaviorId).clone());

		ParticleEmitterInstance particleEmitterInstance;

		particleEmitterInstance.timeRange = descriptor.timeRange;
		particleEmitterInstance.timeRange.spawnTime += elapsedTime;
		particleEmitterInstance.motionState = MotionState{ parentMotionState.position + descriptor.motionState.position, parentMotionState.linearVelocity + descriptor.motionState.linearVelocity, parentMotionState.rotation + descriptor.motionState.rotation, parentMotionState.angularVelocity + descriptor.motionState.angularVelocity };
		particleEmitterInstance.postBehaviorPosition = glm::vec3(0.0f);
		particleEmitterInstance.particleRegistryId = m_particleRegistry.createEntry(particleEmitter.poolId, recursionDepth, particleEmitter.spawnTrigger, particleEmitter.renderDescriptor, std::move(forceFields), std::move(motionBehaviors), std::move(particleBehaviors));
		particleEmitterInstance.trailRegistryId = particleEmitter.trailConfiguration.has_value() ? std::make_optional<unsigned int>(m_trailRegistry.createEntry(particleEmitter.trailConfiguration.value())) : std::nullopt;
		particleEmitterInstance.particleSpawner = m_assetRegistry.getParticleSpawner(particleEmitter.particleSpawnerId).clone();
		particleEmitterInstance.emissionPattern = m_assetRegistry.getEmissionPattern(particleEmitter.emissionPatternId).clone();

		particleEmitterInstance.inheritedForceFields.reserve(descriptor.forceFieldIds.size());
		for (unsigned int forceFieldId : descriptor.forceFieldIds)
			particleEmitterInstance.inheritedForceFields.push_back(m_assetRegistry.getForceField(forceFieldId).clone());

		particleEmitterInstance.inheritedMotionBehaviors.reserve(descriptor.motionBehaviorIds.size());
		for (unsigned int motionBehaviorId : descriptor.motionBehaviorIds)
			particleEmitterInstance.inheritedMotionBehaviors.push_back(m_assetRegistry.getMotionBehavior(motionBehaviorId).clone());

		unsigned int maximumParticleCount = particleEmitterInstance.emissionPattern->getMaximumSimultaneousParticleCount(particleEmitterInstance.particleSpawner->getMaxiumParticleLifetime());
		m_particlePools[particleEmitter.poolId].reserve(maximumParticleCount);
		m_trailPools[particleEmitter.poolId].reserve(maximumParticleCount);
		
		return particleEmitterInstance;
	}

	ParticleSimulation::ParticleSimulation(AssetRegistry& assetRegistry, RandomNumberGenerator& randomNumberGenerator) :
		m_assetRegistry(assetRegistry),
		m_randomNumberGenerator(randomNumberGenerator),
		m_particleEffectInstances(),
		m_particleEmitterInstances(),
		m_particlePools(),
		m_trailPools(),
		m_particleRegistry(),
		m_trailRegistry()
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

	const ParticleRegistry& ParticleSimulation::getParticleRegistry() const
	{
		return m_particleRegistry;
	}

	const TrailRegistry& ParticleSimulation::getTrailRegistry() const
	{
		return m_trailRegistry;
	}

	void ParticleSimulation::addParticleEffect(float elapsedTime, unsigned int id)
	{
		m_particleEffectInstances.push_back(ParticleEffectInstance{ elapsedTime, m_assetRegistry.getParticleEffect(id).emitterDescriptors });
	}

	void ParticleSimulation::clear()
	{
		m_particleEffectInstances.clear();
		m_particleEmitterInstances.clear();
		m_particlePools.clear();
		m_particleRegistry.clear();
		m_trailPools.clear();
		m_trailRegistry.clear();
	}

	void ParticleSimulation::update(float elapsedTime, float deltaTime)
	{
		// Particle effects update
		for (unsigned int i = 0; i < m_particleEffectInstances.size();)
		{
			ParticleEffectInstance& particleEffectInstance = m_particleEffectInstances[i];

			for (unsigned int j = 0; j < particleEffectInstance.emitterDescriptors.size();)
			{
				const ParticleEmitterDescriptor& particleEmitterDescriptor = particleEffectInstance.emitterDescriptors[j];
				if (elapsedTime >= particleEffectInstance.spawnTime + particleEmitterDescriptor.timeRange.spawnTime)
				{
					ParticleEmitterInstance particleEmitterInstance = createParticleEmitter(particleEmitterDescriptor, MotionState{}, 0, elapsedTime);

					m_particleRegistry.addReferenceCount(particleEmitterInstance.particleRegistryId, 1);

					if (particleEmitterInstance.trailRegistryId.has_value())
						m_trailRegistry.addReferenceCount(particleEmitterInstance.trailRegistryId.value(), 1);

					m_particleEmitterInstances.push_back(std::move(particleEmitterInstance));

					particleEffectInstance.emitterDescriptors[j] = std::move(particleEffectInstance.emitterDescriptors.back());
					particleEffectInstance.emitterDescriptors.pop_back();
				}
				else
				{
					++j;
				}
			}

			if (particleEffectInstance.emitterDescriptors.empty())
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
					particleEmitterInstance.postBehaviorPosition += motionBehavior->evaluate(elapsedTime, particleEmitterInstance.motionState);

				unsigned int particleSpawnCount = particleEmitterInstance.emissionPattern->emit(deltaTime);
				if (particleSpawnCount > 0)
				{
					std::vector<Particle> particles = particleEmitterInstance.particleSpawner->spawn(particleSpawnCount, elapsedTime, deltaTime, particleEmitterInstance.particleRegistryId);
					
					const ParticleRegistryEntry& particleRegistryEntry = m_particleRegistry.getEntry(particleEmitterInstance.particleRegistryId);
					ParticlePool& particlePool = m_particlePools.at(particleRegistryEntry.poolId);
					particlePool.reserve(particleSpawnCount);

					bool spawnSpawnTrigger = false;
					ParticleEmitterDescriptor spawnParticleEmitterDescriptor;
					if (particleRegistryEntry.spawnTrigger.has_value())
					{
						const SpawnTrigger& spawnTriggerValue = particleRegistryEntry.spawnTrigger.value();
						spawnSpawnTrigger = particleRegistryEntry.recursionDepth < spawnTriggerValue.maximumRecursionDepth && spawnTriggerValue.spawnEmitterDescriptor.has_value();
						if (spawnSpawnTrigger)
							spawnParticleEmitterDescriptor = spawnTriggerValue.spawnEmitterDescriptor.value();
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
							ParticleEmitterInstance spawnParticleEmitterInstance = createParticleEmitter(spawnParticleEmitterDescriptor, MotionState{ particle.position, particle.linearVelocity, particle.rotation, particle.angularVelocity }, particleRegistryEntry.recursionDepth + 1, elapsedTime);
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
			if (entry.spawnTrigger.has_value() && entry.spawnTrigger.value().periodicEmitterDescriptor.has_value())
			{
				SpawnTrigger& spawnTrigger = entry.spawnTrigger.value();
				if (spawnTrigger.periodicEmitterDescriptor.has_value())
				{
					PeriodicSpawnTrigger& periodicSpawnTrigger = spawnTrigger.periodicEmitterDescriptor.value();
					entry.periodicTriggerAccumulator += deltaTime;

					if (entry.recursionDepth < spawnTrigger.maximumRecursionDepth && entry.periodicTriggerAccumulator >= periodicSpawnTrigger.interval)
					{
						triggeredPeriodicSpawnTriggers.insert(id);
						entry.periodicTriggerAccumulator -= periodicSpawnTrigger.interval;
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
					if (entry.spawnTrigger.has_value())
					{
						const SpawnTrigger& spawnTriggerValue = entry.spawnTrigger.value();
						if (entry.recursionDepth < spawnTriggerValue.maximumRecursionDepth && spawnTriggerValue.deathEmitterDescriptor.has_value())
						{
							ParticleEmitterInstance deathParticleEmitterInstance = createParticleEmitter(spawnTriggerValue.deathEmitterDescriptor.value(), MotionState{ position[i], linearVelocity[i], rotation[i], angularVelocity[i] }, entry.recursionDepth + 1, elapsedTime);
							m_particleRegistry.addReferenceCount(deathParticleEmitterInstance.particleRegistryId, 1);
							if (deathParticleEmitterInstance.trailRegistryId)
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
						ParticleEmitterInstance periodicParticleEmitterInstance = createParticleEmitter(entry.spawnTrigger.value().periodicEmitterDescriptor.value().emitterDescriptor, MotionState{ position[i], linearVelocity[i], rotation[i], angularVelocity[i] }, entry.recursionDepth + 1, elapsedTime);
						m_particleRegistry.addReferenceCount(periodicParticleEmitterInstance.particleRegistryId, 1);
						if (periodicParticleEmitterInstance.trailRegistryId)
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

					for (const std::unique_ptr<MotionBehavior>& motionBehavior : entry.motionBehaviors)
						postBehaviorPosition[i] += motionBehavior->evaluate(elapsedTime, motionState);

					float particleNormalizedAge = (elapsedTime - spawnTime[i]) / lifetime[i];

					for (const std::unique_ptr<ParticleBehavior>& particleBehavior : entry.particleBehaviors)
						particleBehavior->evaluate(elapsedTime, particleNormalizedAge, ParticleView{ color[i], position[i], rotation[i], scale[i], linearVelocity[i], angularVelocity[i], initialColor[i], initialScale[i], postBehaviorPosition[i], phase[i], lifetime[i], spawnTime[i], particleRegistryId[i], id[i] });

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
			std::vector<std::deque<TrailPoint>>& trailPoints = trailPool.getTrailPoints();

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

							trailPoints[i].push_back(TrailPoint{ glm::vec4(1.0f), particlePosition, 1.0f, distanceOnTrail, elapsedTime });

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
					std::deque<TrailPoint>& trail = trailPoints[i];
					unsigned int trailSize = static_cast<unsigned int>(trail.size());

					unsigned int colorGradientSize = static_cast<unsigned int>(trailRegistryEntry.trailConfiguration.colorGradient.size()) + (trailRegistryEntry.trailConfiguration.appendParticleColor ? 1 : 0);
						std::vector<glm::vec4> colorGradient;
						colorGradient.reserve(colorGradientSize);
						if (trailRegistryEntry.trailConfiguration.appendParticleColor)
							colorGradient.push_back(particleColor[i]);
						colorGradient.insert(colorGradient.end(), trailRegistryEntry.trailConfiguration.colorGradient.begin(), trailRegistryEntry.trailConfiguration.colorGradient.end());

					for (unsigned int pointIndex = 0; pointIndex < trail.size(); ++pointIndex)
					{
						float t = 1.0f - (trailSize > 1 ? static_cast<float>(pointIndex) / static_cast<float>(trailSize - 1) : 0.0f);

						switch (trailRegistryEntry.trailConfiguration.thicknessDistribution)
						{
						case TrailThicknessDistribution::Constant: trail[pointIndex].thickness = trailRegistryEntry.trailConfiguration.thickness; break;
						case TrailThicknessDistribution::LinearDecreasing: trail[pointIndex].thickness = (1.0f - t) * trailRegistryEntry.trailConfiguration.thickness; break;
						case TrailThicknessDistribution::QuadraticDecreasing: trail[pointIndex].thickness = (1.0f - t) * (1.0f - t) * trailRegistryEntry.trailConfiguration.thickness; break;
						case TrailThicknessDistribution::LinearIncreasing: trail[pointIndex].thickness = t * trailRegistryEntry.trailConfiguration.thickness; break;
						case TrailThicknessDistribution::QuadraticIncreasing: trail[pointIndex].thickness = t * t * trailRegistryEntry.trailConfiguration.thickness; break;
						}

						if (trailRegistryEntry.trailConfiguration.thicknessEvolution.has_value())
						{
							const TrailThicknessEvolution& trailThicknessEvolution = trailRegistryEntry.trailConfiguration.thicknessEvolution.value();
							float pointAge = (elapsedTime - trail[pointIndex].spawnTime);

							switch (trailThicknessEvolution.distribution)
							{
							case TrailThicknessDistribution::Constant: trail[pointIndex].thickness += pointAge * trailThicknessEvolution.speed; break;
							case TrailThicknessDistribution::LinearDecreasing: trail[pointIndex].thickness += (1.0f - t) * pointAge * trailThicknessEvolution.speed; break;
							case TrailThicknessDistribution::QuadraticDecreasing: trail[pointIndex].thickness += (1.0f - t) * (1.0f - t) * pointAge * trailThicknessEvolution.speed; break;
							case TrailThicknessDistribution::LinearIncreasing: trail[pointIndex].thickness += t * pointAge * trailThicknessEvolution.speed; break;
							case TrailThicknessDistribution::QuadraticIncreasing: trail[pointIndex].thickness += t * t * pointAge * trailThicknessEvolution.speed; break;
							}
						}

						switch (trailRegistryEntry.trailConfiguration.colorInterpolation)
						{
						case TrailColorInterpolation::Constant:
						{
							if (trailRegistryEntry.trailConfiguration.colorStart.has_value())
							{
								const std::vector<float>& colorStart = trailRegistryEntry.trailConfiguration.colorStart.value();
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
						case TrailColorInterpolation::Linear:
						{
							if (trailRegistryEntry.trailConfiguration.colorStart.has_value())
							{
								const std::vector<float>& colorStart = trailRegistryEntry.trailConfiguration.colorStart.value();
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
						
						if (trailRegistryEntry.trailConfiguration.lifetimeFade.has_value())
						{
							float start = trailRegistryEntry.trailConfiguration.lifetimeFade.value().start;
							float end = trailRegistryEntry.trailConfiguration.lifetimeFade.value().end;
	
							float age = elapsedTime - trail[pointIndex].spawnTime;
							float trailFadeT = end > start ? (glm::clamp(age, start, end) - start) / (end - start) : 1.0f;

							trail[pointIndex].color.a *= 1.0f - trailFadeT;
						}
					}

					if (trailRegistryEntry.trailConfiguration.pointLifetime.has_value())
					{
						while (!trail.empty() && elapsedTime >= trail.front().spawnTime + trailRegistryEntry.trailConfiguration.pointLifetime.value())
							trail.pop_front();
					}

					++i;
				}
			}

			for (auto& [trailRegistry, count] : removedTrailCount)
				m_trailRegistry.addReferenceCount(trailRegistry, -static_cast<int>(count));
		}
	}
}