#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonSerialization.hpp"

#include <fstream>

namespace cft
{
	JsonFactory<cft::ForceField> JsonLoader::m_forceFieldFactory;
	JsonFactory<cft::MotionBehavior> JsonLoader::m_motionBehaviorFactory;
	JsonFactory<cft::VisualBehavior> JsonLoader::m_visualBehaviorFactory;
	JsonFactory<cft::EmissionPattern> JsonLoader::m_emissionPatternFactory;
	JsonFactory<cft::ParticleLinker> JsonLoader::m_particleLinkerFactory;
	JsonFactory<cft::RibbonGenerator> JsonLoader::m_ribbonGeneratorFactory;
	JsonFactory<cft::SpawnShape> JsonLoader::m_spawnShapeFactory;
	JsonFactory<cft::LinkRule> JsonLoader::m_linkRuleFactory;
	JsonFactory<lw::Interpolator> JsonLoader::m_interpolatorFactory;
	JsonFactory<lw::Easing> JsonLoader::m_easingFactory;

	bool JsonLoader::m_initialized = false;

	void JsonLoader::loadAssets(const json& data, cft::AssetRegistry& assetRegistry)
	{
		for (const auto& forceFieldData : data.at("forceFields"))
			assetRegistry.addForceField(forceFieldData.at("id"), m_forceFieldFactory.instantiate(forceFieldData));

		for (const auto& motionBehaviorData : data.at("motionBehaviors"))
			assetRegistry.addMotionBehavior(motionBehaviorData.at("id"), m_motionBehaviorFactory.instantiate(motionBehaviorData));

		for (const auto& visualBehaviorData : data.at("visualBehaviors"))
			assetRegistry.addVisualBehavior(visualBehaviorData.at("id"), m_visualBehaviorFactory.instantiate(visualBehaviorData));

		for (const auto& particleSpawnerData : data.at("particleSpawners"))
			assetRegistry.addParticleSpawner(particleSpawnerData.at("id"), particleSpawnerData.get<std::unique_ptr<cft::ParticleSpawner>>());

		for (const auto& emissionPatternData : data.at("emissionPatterns"))
			assetRegistry.addEmissionPattern(emissionPatternData.at("id"), m_emissionPatternFactory.instantiate(emissionPatternData));

		for (const auto& particleLinkerData : data.at("particleLinkers"))
			assetRegistry.addParticleLinker(particleLinkerData.at("id"), m_particleLinkerFactory.instantiate(particleLinkerData));

		for (const auto& ribbonGeneratorData : data.at("ribbonGenerators"))
			assetRegistry.addRibbonGenerator(ribbonGeneratorData.at("id"), m_ribbonGeneratorFactory.instantiate(ribbonGeneratorData));

		for (const auto& imageData : data.at("images"))
			assetRegistry.addImage(imageData.at("id"), imageData.get<cft::Image>());

		for (const auto& modelData : data.at("models"))
			assetRegistry.addModel(modelData.at("id"), modelData.get<cft::Model>());

		for (const auto& spriteSheetDescriptorData : data.at("spriteSheetDescriptors"))
			assetRegistry.addSpriteSheetDescriptor(spriteSheetDescriptorData.at("id"), spriteSheetDescriptorData.get<cft::SpriteSheetDescriptor>());

		for (const auto& particleEffectDescriptorData : data.at("particleEffectDescriptors"))
			assetRegistry.addParticleEffectDescriptor(particleEffectDescriptorData.at("id"), particleEffectDescriptorData.get<cft::ParticleEffectDescriptor>());

		for (const auto& particleEmitterDescriptorData : data.at("particleEmitterDescriptors"))
			assetRegistry.addParticleEmitterDescriptor(particleEmitterDescriptorData.at("id"), particleEmitterDescriptorData.get<cft::ParticleEmitterDescriptor>());
	}

	void JsonLoader::loadBillboardRendererTextures(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry)
	{
		unsigned int width = data.at("width");
		unsigned int height = data.at("height");

		std::vector<unsigned int> imageIds;
		imageIds.reserve(data.at("imageIds").size());

		for (const auto& imageId : data.at("imageIds"))
			imageIds.push_back(imageId);

		particleRenderer.loadBillboardRendererTextures(assetRegistry, imageIds, width, height);
	}

	void JsonLoader::loadMeshRendererTextures(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry)
	{
		std::vector<unsigned int> meshRendererImageIds;
		meshRendererImageIds.reserve(data.size());

		for (const auto& meshRendererImageId : data)
			meshRendererImageIds.push_back(meshRendererImageId);

		particleRenderer.loadMeshRendererTextures(assetRegistry, meshRendererImageIds);
	}

	void JsonLoader::loadMeshRendererMeshes(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry)
	{
		std::vector<unsigned int> meshRendererModelIds;
		meshRendererModelIds.reserve(data.size());

		for (const auto& meshRendererModelId : data)
			meshRendererModelIds.push_back(meshRendererModelId);

		particleRenderer.loadMeshRendererMeshes(assetRegistry, meshRendererModelIds);
	}

	void JsonLoader::initialize()
	{
		if (m_initialized)
			return;

		registerTypes(m_forceFieldFactory);
		registerTypes(m_motionBehaviorFactory);
		registerTypes(m_visualBehaviorFactory);
		registerTypes(m_emissionPatternFactory);
		registerTypes(m_particleLinkerFactory);
		registerTypes(m_ribbonGeneratorFactory);
		registerTypes(m_spawnShapeFactory);
		registerTypes(m_linkRuleFactory);
		registerTypes(m_interpolatorFactory);
		registerTypes(m_easingFactory);

		m_initialized = true;
	}

	void JsonLoader::load(const std::string& path, cft::ParticleSimulation& particleSimulation, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry)
	{
		std::ifstream file(path);
		json data = json::parse(file);

		particleSimulation.setSeed(data.at("seed"));

		loadAssets(data.at("assets"), assetRegistry);

		loadBillboardRendererTextures(data.at("billboardRendererImages"), particleRenderer, assetRegistry);
		loadMeshRendererTextures(data.at("meshRendererImageIds"), particleRenderer, assetRegistry);
		loadMeshRendererMeshes(data.at("meshRendererModelIds"), particleRenderer, assetRegistry);
	}

	JsonFactory<cft::ForceField>& JsonLoader::getForceFieldFactory()
	{
		return m_forceFieldFactory;
	}

	JsonFactory<cft::MotionBehavior>& JsonLoader::getMotionBehaviorFactory()
	{
		return m_motionBehaviorFactory;
	}

	JsonFactory<cft::VisualBehavior>& JsonLoader::getVisualBehaviorFactory()
	{
		return m_visualBehaviorFactory;
	}

	JsonFactory<cft::EmissionPattern>& JsonLoader::getEmissionPatternFactory()
	{
		return m_emissionPatternFactory;
	}

	JsonFactory<cft::ParticleLinker>& JsonLoader::getParticleLinkerFactory()
	{
		return m_particleLinkerFactory;
	}

	JsonFactory<cft::RibbonGenerator>& JsonLoader::getRibbonGeneratorFactory()
	{
		return m_ribbonGeneratorFactory;
	}

	JsonFactory<cft::SpawnShape>& JsonLoader::getSpawnShapeFactory()
	{
		return m_spawnShapeFactory;
	}

	JsonFactory<cft::LinkRule>& JsonLoader::getLinkRuleFactory()
	{
		return m_linkRuleFactory;
	}

	JsonFactory<lw::Interpolator>& JsonLoader::getInterpolatorFactory()
	{
		return m_interpolatorFactory;
	}

	JsonFactory<lw::Easing>& JsonLoader::getEasingFactory()
	{
		return m_easingFactory;
	}
}