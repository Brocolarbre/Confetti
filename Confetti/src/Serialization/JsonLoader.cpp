#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonSerialization.hpp"
#include "Confetti/ParticleSystem.hpp"

#include <fstream>
#include <iostream>

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

	bool JsonLoader::loadBillboardRendererTextures(const json& data, ParticleRenderer& particleRenderer, AssetRegistry& assetRegistry)
	{
		unsigned int width = data.at("width");
		unsigned int height = data.at("height");

		std::vector<unsigned int> imageIds;
		imageIds.reserve(data.at("imageIds").size());

		for (const auto& imageId : data.at("imageIds"))
			imageIds.push_back(imageId);

		return particleRenderer.loadBillboardRendererTextures(assetRegistry, imageIds, width, height);
	}

	bool JsonLoader::loadPathRendererTextures(const json& data, ParticleRenderer& particleRenderer, AssetRegistry& assetRegistry)
	{
		unsigned int width = data.at("width");
		unsigned int height = data.at("height");

		std::vector<unsigned int> imageIds;
		imageIds.reserve(data.at("imageIds").size());

		for (const auto& imageId : data.at("imageIds"))
			imageIds.push_back(imageId);

		return particleRenderer.loadPathRendererTextures(assetRegistry, imageIds, width, height);
	}

	bool JsonLoader::loadMeshRendererTextures(const json& data, ParticleRenderer& particleRenderer, AssetRegistry& assetRegistry)
	{
		std::vector<unsigned int> meshRendererImageIds;
		meshRendererImageIds.reserve(data.size());

		for (const auto& meshRendererImageId : data)
			meshRendererImageIds.push_back(meshRendererImageId);

		return particleRenderer.loadMeshRendererTextures(assetRegistry, meshRendererImageIds);
	}

	bool JsonLoader::loadMeshRendererMeshes(const json& data, ParticleRenderer& particleRenderer, AssetRegistry& assetRegistry)
	{
		std::vector<unsigned int> meshRendererModelIds;
		meshRendererModelIds.reserve(data.size());

		for (const auto& meshRendererModelId : data)
			meshRendererModelIds.push_back(meshRendererModelId);

		return particleRenderer.loadMeshRendererMeshes(assetRegistry, meshRendererModelIds);
	}

	void JsonLoader::clearFactories()
	{
		m_forceFieldFactory.clear();
		m_motionBehaviorFactory.clear();
		m_visualBehaviorFactory.clear();
		m_emissionPatternFactory.clear();
		m_particleLinkerFactory.clear();
		m_ribbonGeneratorFactory.clear();
		m_spawnShapeFactory.clear();
		m_linkRuleFactory.clear();
		m_interpolatorFactory.clear();
		m_easingFactory.clear();
	}

	void JsonLoader::initialize(const ProviderRegistry& providerRegistry)
	{
		clearFactories();

		registerTypes(m_forceFieldFactory, providerRegistry);
		registerTypes(m_motionBehaviorFactory, providerRegistry);
		registerTypes(m_visualBehaviorFactory, providerRegistry);
		registerTypes(m_emissionPatternFactory, providerRegistry);
		registerTypes(m_particleLinkerFactory, providerRegistry);
		registerTypes(m_ribbonGeneratorFactory, providerRegistry);
		registerTypes(m_spawnShapeFactory, providerRegistry);
		registerTypes(m_linkRuleFactory, providerRegistry);
		registerTypes(m_interpolatorFactory, providerRegistry);
		registerTypes(m_easingFactory, providerRegistry);
	}

	bool JsonLoader::load(const std::string& path, ParticleSystem& particleSystem)
	{
		std::ifstream file(path);
		json data = json::parse(file);

		AssetRegistry& assetRegistry = particleSystem.getAssetRegistry();
		ParticleSimulation& particleSimulation = particleSystem.getParticleSimulation();
		ParticleRenderer& particleRenderer = particleSystem.getParticleRenderer();

		try
		{
			particleSimulation.setSeed(data.at("seed"));

			loadAssets(data.at("assets"), assetRegistry);

			const json& billboardRendererImages = data.at("billboardRendererImages");
			if (!billboardRendererImages.is_null())
			{
				if (!loadBillboardRendererTextures(billboardRendererImages, particleRenderer, assetRegistry))
					return false;
			}

			const json& pathRendererImages = data.at("pathRendererImages");
			if (!pathRendererImages.is_null())
			{
				if (!loadPathRendererTextures(pathRendererImages, particleRenderer, assetRegistry))
					return false;
			}

			if (!loadMeshRendererTextures(data.at("meshRendererImageIds"), particleRenderer, assetRegistry))
				return false;
			
			if (!loadMeshRendererMeshes(data.at("meshRendererModelIds"), particleRenderer, assetRegistry))
				return false;
		}
		catch (const json::parse_error& error)
		{
			std::cerr << "JSON loader parsing error : " << error.what() << std::endl;
			return false;
		}
		catch (const json::out_of_range& error)
		{
			std::cerr << "JSON loader missing key error : " << error.what() << std::endl;
			return false;
		}
		catch (const std::exception& error)
		{
			std::cerr << "JSON loader error : " << error.what() << std::endl;
			return false;
		}

		return true;
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
}