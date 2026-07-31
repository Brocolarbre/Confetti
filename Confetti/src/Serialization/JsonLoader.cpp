#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonSerialization.hpp"
#include "Confetti/ParticleSystem.hpp"

#include <fstream>

namespace cft
{
	JsonFactory<ForceField> JsonLoader::m_forceFieldFactory;
	JsonFactory<MotionBehavior> JsonLoader::m_motionBehaviorFactory;
	JsonFactory<VisualBehavior> JsonLoader::m_visualBehaviorFactory;
	JsonFactory<EmissionPattern> JsonLoader::m_emissionPatternFactory;
	JsonFactory<ParticleLinker> JsonLoader::m_particleLinkerFactory;
	JsonFactory<RibbonGenerator> JsonLoader::m_ribbonGeneratorFactory;
	JsonFactory<SpawnShape> JsonLoader::m_spawnShapeFactory;
	JsonFactory<LinkRule> JsonLoader::m_linkRuleFactory;
	JsonFactory<lw::Interpolator> JsonLoader::m_interpolatorFactory;
	JsonFactory<lw::Easing> JsonLoader::m_easingFactory;

	ProviderRegistry JsonLoader::m_providerRegistry;

	bool JsonLoader::m_initialized = false;

	void JsonLoader::loadAssets(const json& data, AssetRegistry& assetRegistry)
	{
		for (const auto& forceFieldData : data.at("forceFields"))
			assetRegistry.addForceField(forceFieldData.at("id"), m_forceFieldFactory.instantiate(forceFieldData));

		for (const auto& motionBehaviorData : data.at("motionBehaviors"))
			assetRegistry.addMotionBehavior(motionBehaviorData.at("id"), m_motionBehaviorFactory.instantiate(motionBehaviorData));

		for (const auto& visualBehaviorData : data.at("visualBehaviors"))
			assetRegistry.addVisualBehavior(visualBehaviorData.at("id"), m_visualBehaviorFactory.instantiate(visualBehaviorData));

		for (const auto& particleSpawnerData : data.at("particleSpawners"))
			assetRegistry.addParticleSpawner(particleSpawnerData.at("id"), particleSpawnerData.get<std::unique_ptr<ParticleSpawner>>());

		for (const auto& emissionPatternData : data.at("emissionPatterns"))
			assetRegistry.addEmissionPattern(emissionPatternData.at("id"), m_emissionPatternFactory.instantiate(emissionPatternData));

		for (const auto& particleLinkerData : data.at("particleLinkers"))
			assetRegistry.addParticleLinker(particleLinkerData.at("id"), m_particleLinkerFactory.instantiate(particleLinkerData));

		for (const auto& ribbonGeneratorData : data.at("ribbonGenerators"))
			assetRegistry.addRibbonGenerator(ribbonGeneratorData.at("id"), m_ribbonGeneratorFactory.instantiate(ribbonGeneratorData));

		for (const auto& imageData : data.at("images"))
			assetRegistry.addImage(imageData.at("id"), imageData.get<Image>());

		for (const auto& modelData : data.at("models"))
			assetRegistry.addModel(modelData.at("id"), modelData.get<Model>());

		for (const auto& spriteSheetDescriptorData : data.at("spriteSheetDescriptors"))
			assetRegistry.addSpriteSheetDescriptor(spriteSheetDescriptorData.at("id"), spriteSheetDescriptorData.get<SpriteSheetDescriptor>());

		for (const auto& particleEffectDescriptorData : data.at("particleEffectDescriptors"))
			assetRegistry.addParticleEffectDescriptor(particleEffectDescriptorData.at("id"), particleEffectDescriptorData.get<ParticleEffectDescriptor>());

		for (const auto& particleEmitterDescriptorData : data.at("particleEmitterDescriptors"))
			assetRegistry.addParticleEmitterDescriptor(particleEmitterDescriptorData.at("id"), particleEmitterDescriptorData.get<ParticleEmitterDescriptor>());
	}

	void JsonLoader::loadBillboardRendererTextures(const json& data, ParticleRenderer& particleRenderer, AssetRegistry& assetRegistry)
	{
		unsigned int width = data.at("width");
		unsigned int height = data.at("height");

		std::vector<unsigned int> imageIds;
		imageIds.reserve(data.at("imageIds").size());

		for (const auto& imageId : data.at("imageIds"))
			imageIds.push_back(imageId);

		particleRenderer.loadBillboardRendererTextures(assetRegistry, imageIds, width, height);
	}

	void JsonLoader::loadMeshRendererTextures(const json& data, ParticleRenderer& particleRenderer, AssetRegistry& assetRegistry)
	{
		std::vector<unsigned int> meshRendererImageIds;
		meshRendererImageIds.reserve(data.size());

		for (const auto& meshRendererImageId : data)
			meshRendererImageIds.push_back(meshRendererImageId);

		particleRenderer.loadMeshRendererTextures(assetRegistry, meshRendererImageIds);
	}

	void JsonLoader::loadMeshRendererMeshes(const json& data, ParticleRenderer& particleRenderer, AssetRegistry& assetRegistry)
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

		registerTypes(m_forceFieldFactory, m_providerRegistry);
		registerTypes(m_motionBehaviorFactory, m_providerRegistry);
		registerTypes(m_visualBehaviorFactory, m_providerRegistry);
		registerTypes(m_emissionPatternFactory, m_providerRegistry);
		registerTypes(m_particleLinkerFactory, m_providerRegistry);
		registerTypes(m_ribbonGeneratorFactory, m_providerRegistry);
		registerTypes(m_spawnShapeFactory, m_providerRegistry);
		registerTypes(m_linkRuleFactory, m_providerRegistry);
		registerTypes(m_interpolatorFactory, m_providerRegistry);
		registerTypes(m_easingFactory, m_providerRegistry);

		m_initialized = true;
	}

	void JsonLoader::load(const std::string& path, ParticleSystem& particleSystem)
	{
		std::ifstream file(path);
		json data = json::parse(file);

		particleSystem.m_simulation.setSeed(data.at("seed"));

		loadAssets(data.at("assets"), particleSystem.m_assetRegistry);

		loadBillboardRendererTextures(data.at("billboardRendererImages"), particleSystem.m_renderer, particleSystem.m_assetRegistry);
		loadMeshRendererTextures(data.at("meshRendererImageIds"), particleSystem.m_renderer, particleSystem.m_assetRegistry);
		loadMeshRendererMeshes(data.at("meshRendererModelIds"), particleSystem.m_renderer, particleSystem.m_assetRegistry);
	}

	JsonFactory<ForceField>& JsonLoader::getForceFieldFactory()
	{
		return m_forceFieldFactory;
	}

	JsonFactory<MotionBehavior>& JsonLoader::getMotionBehaviorFactory()
	{
		return m_motionBehaviorFactory;
	}

	JsonFactory<VisualBehavior>& JsonLoader::getVisualBehaviorFactory()
	{
		return m_visualBehaviorFactory;
	}

	JsonFactory<EmissionPattern>& JsonLoader::getEmissionPatternFactory()
	{
		return m_emissionPatternFactory;
	}

	JsonFactory<ParticleLinker>& JsonLoader::getParticleLinkerFactory()
	{
		return m_particleLinkerFactory;
	}

	JsonFactory<RibbonGenerator>& JsonLoader::getRibbonGeneratorFactory()
	{
		return m_ribbonGeneratorFactory;
	}

	JsonFactory<SpawnShape>& JsonLoader::getSpawnShapeFactory()
	{
		return m_spawnShapeFactory;
	}

	JsonFactory<LinkRule>& JsonLoader::getLinkRuleFactory()
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

	ProviderRegistry& JsonLoader::getProviderRegistry()
	{
		return m_providerRegistry;
	}
}