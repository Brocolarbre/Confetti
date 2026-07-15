#include "Confetti/RibbonGenerator/RibbonGenerator.hpp"

namespace cft
{
	void RibbonGenerator::update(RibbonPool& ribbonPool, const ParticlePool& particlePool)
	{
		const std::vector<glm::vec4>& color = particlePool.getColor();
		const std::vector<glm::vec3>& position = particlePool.getPosition();
		const std::vector<glm::quat>& rotation = particlePool.getRotation();
		const std::vector<glm::vec3>& scale = particlePool.getScale();
		const std::vector<glm::vec3>& linearVelocity = particlePool.getLinearVelocity();
		const std::vector<glm::vec3>& angularVelocity = particlePool.getAngularVelocity();
		const std::vector<glm::vec4>& initialColor = particlePool.getInitialColor();
		const std::vector<glm::vec3>& initialScale = particlePool.getInitialScale();
		const std::vector<glm::vec3>& postBehaviorPosition = particlePool.getPostBehaviorPosition();
		const std::vector<float>& phase = particlePool.getPhase();
		const std::vector<float>& lifetime = particlePool.getLifetime();
		const std::vector<float>& spawnTime = particlePool.getSpawnTime();
		const std::vector<unsigned int>& id = particlePool.getId();
		const std::vector<unsigned int>& particleRegistryId = particlePool.getParticleRegistryId();

		const std::vector<unsigned int>& ribbonRegistryId = ribbonPool.getRibbonRegistryId();
		const std::vector<unsigned int>& fromParticleId = ribbonPool.getFromParticleId();
		const std::vector<unsigned int>& toParticleId = ribbonPool.getToParticleId();

		for (unsigned int i = 0; i < ribbonPool.getCount();)
		{
			std::optional<unsigned int> fromParticleIndex = particlePool.getIndex(fromParticleId[i]);
			std::optional<unsigned int> toParticleIndex = particlePool.getIndex(fromParticleId[i]);

			if (!fromParticleIndex.has_value() || !toParticleIndex.has_value())
			{
				ribbonPool.remove(i);
			}
			else
			{
				RibbonView ribbon{ ribbonRegistryId[i], fromParticleId[i], toParticleId[i] };

				unsigned int fromParticleIndexValue = fromParticleIndex.value();
				unsigned int toParticleIndexValue = toParticleIndex.value();

				ConstantParticleView fromParticle{ color[fromParticleIndexValue], position[fromParticleIndexValue], rotation[fromParticleIndexValue], scale[fromParticleIndexValue], linearVelocity[fromParticleIndexValue], angularVelocity[fromParticleIndexValue], initialColor[fromParticleIndexValue], initialScale[fromParticleIndexValue], postBehaviorPosition[fromParticleIndexValue], phase[fromParticleIndexValue], lifetime[fromParticleIndexValue], spawnTime[fromParticleIndexValue], particleRegistryId[fromParticleIndexValue], id[fromParticleIndexValue] };
				ConstantParticleView toParticle{ color[toParticleIndexValue], position[toParticleIndexValue], rotation[toParticleIndexValue], scale[toParticleIndexValue], linearVelocity[toParticleIndexValue], angularVelocity[toParticleIndexValue], initialColor[toParticleIndexValue], initialScale[toParticleIndexValue], postBehaviorPosition[toParticleIndexValue], phase[toParticleIndexValue], lifetime[toParticleIndexValue], spawnTime[toParticleIndexValue], particleRegistryId[toParticleIndexValue], id[toParticleIndexValue] };

				if (isRibbonValid(ribbon, fromParticle, toParticle))
				{
					updateRibbon(ribbon);
					++i;
				}
				else
				{
					ribbonPool.remove(i);
				}
			}
		}

		createRibbons(ribbonPool, particlePool);
	}
}