#include "JsonLoader.hpp"
#include "JsonLoaderAttributeGenerator.hpp"

#include <Confetti/Behavior/Force/AttractionForceField.hpp>
#include <Confetti/Behavior/Force/DirectionalForceField.hpp>
#include <Confetti/Behavior/Force/LinearDragForceField.hpp>
#include <Confetti/Behavior/Force/OrbitForceField.hpp>
#include <Confetti/Behavior/Force/QuadraticDragForceField.hpp>
#include <Confetti/Behavior/Force/RepulsionForceField.hpp>
#include <Confetti/Behavior/Force/ShockWaveForceField.hpp>
#include <Confetti/Behavior/Force/TurbulenceForceField.hpp>
#include <Confetti/Behavior/Force/VortexForceField.hpp>
#include <Confetti/Behavior/Force/WindForceField.hpp>

#include <Confetti/Behavior/Motion/CircleMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/FigureEightMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/JitterMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/OrbitMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/OscillationMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/PathMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/SegmentMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/SpiralMotionBehavior.hpp>

#include <Confetti/Behavior/Visual/ColorShiftVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/DimOutVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/FadeInVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/FadeOutVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/FlickerVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/GrowInVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/PulseVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/ShrinkOutVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/SmoothColorShiftVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/SquashStretchVisualBehavior.hpp>

#include <Confetti/Emission/EmissionPattern/ConstantRateEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/FixedBurstEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/LinearBurstEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/LinearRateEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/PeriodicBurstEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/RandomRateEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/SingleBurstEmissionPattern.hpp>

#include <Confetti/Simulation/Link/ParticleLinker/ChainParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/KNearestNeighborParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/NearestNeighborParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/OriginParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/RandomParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/TargetParticleLinker.hpp>

#include <Confetti/Simulation/Link/RibbonGenerator/PathRibbonGenerator.hpp>
#include <Confetti/Simulation/Link/RibbonGenerator/SegmentRibbonGenerator.hpp>
#include <Confetti/Simulation/Link/RibbonGenerator/SpiralRibbonGenerator.hpp>
#include <Confetti/Simulation/Link/RibbonGenerator/WaveRibbonGenerator.hpp>

#include <fstream>

using json = nlohmann::json;

std::unique_ptr<cft::ForceField> JsonLoader::parseForceField(const json& data)
{
	std::string type = data.at("type");

	if (type == "Attraction")
		return std::make_unique<cft::AttractionForceField>(data.at("spatialInfluence").get<cft::SpatialInfluence>(), data.at("strength"));
	else if (type == "Directional")
		return std::make_unique<cft::DirectionalForceField>(data.at("direction").get<Vec3>().value, data.at("strength"));
	else if (type == "Linear")
		return std::make_unique<cft::LinearDragForceField>(data.at("strength"));
	else if (type == "Orbit")
		return std::make_unique<cft::OrbitForceField>(data.at("spatialInfluence").get<cft::SpatialInfluence>(), data.at("axis").get<Vec3>().value, data.at("strength"), data.at("radius"), data.at("radialCorrectionStrength"));
	else if (type == "QuadraticDrag")
		return std::make_unique<cft::QuadraticDragForceField>(data.at("strength"));
	else if (type == "Repulsion")
		return std::make_unique<cft::RepulsionForceField>(data.at("spatialInfluence").get<cft::SpatialInfluence>(), data.at("strength"));
	else if (type == "ShockWave")
		return std::make_unique<cft::ShockWaveForceField>(data.at("spatialInfluence").get<cft::SpatialInfluence>(), data.at("axis").get<Vec3>().value, data.at("speed"), data.at("strength"), data.at("thickness"));
	else if (type == "Turbulence")
		return std::make_unique<cft::TurbulenceForceField>(data.at("strength"), data.at("seed"));
	else if (type == "Vortex")
		return std::make_unique<cft::VortexForceField>(data.at("spatialInfluence").get<cft::SpatialInfluence>(), data.at("axis").get<Vec3>().value, data.at("strength"), data.at("pullStrength"));
	else if (type == "Wind")
		return std::make_unique<cft::WindForceField>(data.at("direction").get<Vec3>().value, data.at("strength"), data.at("drag"));
	else
		throw std::runtime_error("Invalid force field type : '" + type + "'");
}

std::unique_ptr<cft::MotionBehavior> JsonLoader::parseMotionBehavior(const json& data)
{
	std::string type = data.at("type");

	if (type == "Circle")
		return std::make_unique<cft::CircleMotionBehavior>(data.at("axis").get<Vec3>().value, data.at("radius"), data.at("speed"));
	else if (type == "FigureEight")
		return std::make_unique<cft::FigureEightMotionBehavior>(data.at("axis").get<Vec3>().value, data.at("radius"), data.at("speed"));
	else if (type == "Jitter")
		return std::make_unique<cft::JitterMotionBehavior>(data.at("strength"), data.at("seed"));
	else if (type == "Orbit")
		return std::make_unique<cft::OrbitMotionBehavior>(data.at("origin").get<Vec3>().value, data.at("axis").get<Vec3>().value, data.at("radius"), data.at("speed"));
	else if (type == "Oscillation")
		return std::make_unique<cft::OscillationMotionBehavior>(data.at("from").get<Vec3>().value, data.at("to").get<Vec3>().value, data.at("speed"));
	else if (type == "Path")
		return std::make_unique<cft::PathMotionBehavior>(data.at("path").get<std::vector<lw::Point>>(), data.at("interpolator").get<std::unique_ptr<lw::Interpolator>>(), JsonTools::parseOptionalPointer<lw::Easing>(data.at("easing")), data.at("speed"));
	else if (type == "Segment")
		return std::make_unique<cft::SegmentMotionBehavior>(data.at("from").get<Vec3>().value, data.at("to").get<Vec3>().value, data.at("speed"));
	else if (type == "Spiral")
		return std::make_unique<cft::SpiralMotionBehavior>(data.at("origin").get<Vec3>().value, data.at("axis").get<Vec3>().value, data.at("startRadius"), data.at("growth"), data.at("speed"), data.at("rise"));
	else
		throw std::runtime_error("Invalid motion behavior type : '" + type + "'");
}

std::unique_ptr<cft::VisualBehavior> JsonLoader::parseVisualBehavior(const json& data)
{
	std::string type = data.at("type");

	if (type == "ColorShift")
		return std::make_unique<cft::ColorShiftVisualBehavior>(JsonTraits<cft::Color, Color>::readVector(data.at("colors")), data.at("speed"), data.at("cyclic"));
	if (type == "DimOut")
		return std::make_unique<cft::DimOutVisualBehavior>(data.at("duration").get<cft::ParticleTime>());
	if (type == "FadeIn")
		return std::make_unique<cft::FadeInVisualBehavior>(data.at("duration").get<cft::ParticleTime>());
	if (type == "FadeOut")
		return std::make_unique<cft::FadeOutVisualBehavior>(data.at("duration").get<cft::ParticleTime>());
	if (type == "Flicker")
		return std::make_unique<cft::FlickerVisualBehavior>(data.at("minimumBrightness"), data.at("maximumBrightness"), data.at("speed"));
	if (type == "GrowIn")
		return std::make_unique<cft::GrowInVisualBehavior>(data.at("duration").get<cft::ParticleTime>());
	if (type == "Pulse")
		return std::make_unique<cft::PulseVisualBehavior>(data.at("colorA").get<Color>().value, data.at("colorB").get<Color>().value, data.at("speed"));
	if (type == "ShrinkOut")
		return std::make_unique<cft::ShrinkOutVisualBehavior>(data.at("duration").get<cft::ParticleTime>());
	if (type == "SmoothColorShift")
		return std::make_unique<cft::SmoothColorShiftVisualBehavior>(JsonTraits<cft::Color, Color>::readVector(data.at("colors")), data.at("speed"), data.at("cyclic"));
	if (type == "SquashStretch")
		return std::make_unique<cft::SquashStretchVisualBehavior>(data.at("strength").get<Vec2>().value, data.at("speed"));
	else
		throw std::runtime_error("Invalid visual behavior type : '" + type + "'");
}

std::unique_ptr<cft::ParticleSpawner> JsonLoader::parseParticleSpawner(const json& data)
{
	if (data.contains("spawnShape"))
	{
		return std::make_unique<cft::ParticleSpawner>(
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Color, Color>(data.at("colorAttributeGenerator")),
			data.at("spawnShape").get<std::unique_ptr<cft::SpawnShape>>(),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Rotation, Vec3>(data.at("rotationAttributeGenerator")),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Scale, Vec3>(data.at("scaleAttributeGenerator")),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::LinearVelocity, Vec3>(data.at("linearVelocityAttributeGenerator")),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::AngularVelocity, Vec3>(data.at("angularVelocityAttributeGenerator")),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Phase, float>(data.at("phaseAttributeGenerator")),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Lifetime, float>(data.at("lifetimeAttributeGenerator")),
			data.at("maximumParticleLifetime")
		);
	}
	else
	{
		return std::make_unique<cft::ParticleSpawner>(
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Color, Color>(data.at("colorAttributeGenerator")),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Position, Vec3>(data.at("positionAttributeGenerator")),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Rotation, Vec3>(data.at("rotationAttributeGenerator")),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Scale, Vec3>(data.at("scaleAttributeGenerator")),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::LinearVelocity, Vec3>(data.at("linearVelocityAttributeGenerator")),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::AngularVelocity, Vec3>(data.at("angularVelocityAttributeGenerator")),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Phase, float>(data.at("phaseAttributeGenerator")),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Lifetime, float>(data.at("lifetimeAttributeGenerator")),
			data.at("maximumParticleLifetime")
		);
	}
}

std::unique_ptr<cft::EmissionPattern> JsonLoader::parseEmissionPattern(const json& data)
{
	std::string type = data.at("type");

	if (type == "ConstantRate")
		return std::make_unique<cft::ConstantRateEmissionPattern>(data.at("rate"));
	else if (type == "FixedBurst")
		return std::make_unique<cft::FixedBurstEmissionPattern>(data.at("count"), data.at("burstCount"), data.at("interval"));
	else if (type == "LinearBurst")
		return std::make_unique<cft::LinearBurstEmissionPattern>(data.at("count"), data.at("initialInterval"), data.at("finalInterval"), data.at("transitionDuration"));
	else if (type == "LinearRate")
		return std::make_unique<cft::LinearRateEmissionPattern>(data.at("initialRate"), data.at("finalRate"), data.at("transitionDuration"));
	else if (type == "PeriodicBurst")
		return std::make_unique<cft::PeriodicBurstEmissionPattern>(data.at("count"), data.at("interval"));
	else if (type == "RandomRate")
		return std::make_unique<cft::RandomRateEmissionPattern>(data.at("minimumRate"), data.at("maximumRate"), data.at("seed"));
	else if (type == "SingleBurst")
		return std::make_unique<cft::SingleBurstEmissionPattern>(data.at("count"));
	else
		throw std::runtime_error("Invalid emission pattern type : '" + type + "'");
}

std::unique_ptr<cft::ParticleLinker> JsonLoader::parseParticleLinker(const json& data)
{
	std::string type = data.at("type");

	std::vector<std::unique_ptr<cft::LinkRule>> connectionRules = data.at("connectionRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>();
	std::vector<std::unique_ptr<cft::LinkRule>> validationRules = data.at("validationRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>();

	if (type == "Chain")
		return std::make_unique<cft::ChainParticleLinker>(std::move(connectionRules), std::move(validationRules));
	else if (type == "KNearestNeighbor")
		return std::make_unique<cft::KNearestNeighborParticleLinker>(std::move(connectionRules), std::move(validationRules), data.at("neighborCount"));
	else if (type == "NearestNeighbor")
		return std::make_unique<cft::NearestNeighborParticleLinker>(std::move(connectionRules), std::move(validationRules));
	else if (type == "Origin")
		return std::make_unique<cft::OriginParticleLinker>(std::move(connectionRules), std::move(validationRules), data.at("origin").get<Vec3>().value);
	else if (type == "Random")
		return std::make_unique<cft::RandomParticleLinker>(std::move(connectionRules), std::move(validationRules), data.at("connectionCount"), data.at("seed"));
	else if (type == "Target")
		return std::make_unique<cft::TargetParticleLinker>(std::move(connectionRules), std::move(validationRules), data.at("targetParticleId"));
	else
		throw std::runtime_error("Invalid particle linker type : '" + type + "'");
}

std::unique_ptr<cft::RibbonGenerator> JsonLoader::parseRibbonGenerator(const json& data)
{
	std::string type = data.at("type");

	if (type == "Path")
		return std::make_unique<cft::PathRibbonGenerator>(data.at("path").get<std::vector<lw::Point>>(), data.at("interpolator").get<std::unique_ptr<lw::Interpolator>>(), JsonTools::parseOptionalPointer<lw::Easing>(data.at("easing")));
	else if (type == "Segment")
		return std::make_unique<cft::SegmentRibbonGenerator>();
	else if (type == "Spiral")
		return std::make_unique<cft::SpiralRibbonGenerator>(data.at("frequency"), data.at("radius"), data.at("animationSpeed"));
	else if (type == "Wave")
		return std::make_unique<cft::WaveRibbonGenerator>(data.at("frequency"), data.at("amplitude"), data.at("animationSpeed"));
	else
		throw std::runtime_error("Invalid ribbon generator type : '" + type + "'");
}

cft::Image JsonLoader::parseImage(const json& data)
{
	cft::Image image;
	image.loadFromFile(data.at("path"));

	return image;
}

cft::Model JsonLoader::parseModel(const json& data)
{
	cft::Model model;
	model.loadFromFile(data.at("path"));

	return model;
}

cft::SpriteSheetDescriptor JsonLoader::parseSpriteSheetDescriptor(const json& data)
{
	return cft::SpriteSheetDescriptor{
		data.at("imageId"),
		data.at("frameCount"),
		data.at("rowFrameCount"),
		data.at("frameWidth"),
		data.at("frameHeight"),
		data.at("animationSpeed")
	};
}

cft::ParticleEffectDescriptor JsonLoader::parseParticleEffectDescriptor(const json& data)
{
	return cft::ParticleEffectDescriptor{
		data.at("emitterSpawnContexts").get<std::vector<cft::ParticleEmitterSpawnContext>>()
	};
}

cft::ParticleEmitterDescriptor JsonLoader::parseParticleEmitterDescriptor(const json& data)
{
	return cft::ParticleEmitterDescriptor{
		data.at("poolId"),
		data.at("particleSpawnerId"),
		data.at("emissionPatternId"),
		JsonTools::parseOptional<cft::TrailConfiguration>(data.at("trailConfiguration")),
		JsonTools::parseOptional<cft::RibbonConfiguration>(data.at("ribbonConfiguration")),
		JsonTools::parseOptional<cft::SpawnTriggerDescriptor>(data.at("spawnTriggerDescriptor")),
		data.at("renderConfiguration").get<cft::RenderConfiguration>(),
		data.at("forceFieldIds").get<std::vector<unsigned int>>(),
		data.at("motionBehaviorIds").get<std::vector<unsigned int>>(),
		data.at("visualBehaviorIds").get<std::vector<unsigned int>>()
	};
}

void JsonLoader::loadAssets(const json& data, cft::AssetRegistry& assetRegistry)
{
	for (const auto& forceFieldData : data.at("forceFields"))
		assetRegistry.addForceField(forceFieldData.at("id"), parseForceField(forceFieldData));

	for (const auto& motionBehaviorData : data.at("motionBehaviors"))
		assetRegistry.addMotionBehavior(motionBehaviorData.at("id"), parseMotionBehavior(motionBehaviorData));

	for (const auto& visualBehaviorData : data.at("visualBehaviors"))
		assetRegistry.addVisualBehavior(visualBehaviorData.at("id"), parseVisualBehavior(visualBehaviorData));

	for (const auto& particleSpawnerData : data.at("particleSpawners"))
		assetRegistry.addParticleSpawner(particleSpawnerData.at("id"), parseParticleSpawner(particleSpawnerData));

	for (const auto& emissionPatternData : data.at("emissionPatterns"))
		assetRegistry.addEmissionPattern(emissionPatternData.at("id"), parseEmissionPattern(emissionPatternData));

	for (const auto& particleLinkerData : data.at("particleLinkers"))
		assetRegistry.addParticleLinker(particleLinkerData.at("id"), parseParticleLinker(particleLinkerData));

	for (const auto& ribbonGeneratorData : data.at("ribbonGenerators"))
		assetRegistry.addRibbonGenerator(ribbonGeneratorData.at("id"), parseRibbonGenerator(ribbonGeneratorData));

	for (const auto& imageData : data.at("images"))
		assetRegistry.addImage(imageData.at("id"), parseImage(imageData));

	for (const auto& modelData : data.at("models"))
		assetRegistry.addModel(modelData.at("id"), parseModel(modelData));

	for (const auto& spriteSheetDescriptorData : data.at("spriteSheetDescriptors"))
		assetRegistry.addSpriteSheetDescriptor(spriteSheetDescriptorData.at("id"), parseSpriteSheetDescriptor(spriteSheetDescriptorData));

	for (const auto& particleEffectDescriptorData : data.at("particleEffectDescriptors"))
		assetRegistry.addParticleEffectDescriptor(particleEffectDescriptorData.at("id"), parseParticleEffectDescriptor(particleEffectDescriptorData));

	for (const auto& particleEmitterDescriptorData : data.at("particleEmitterDescriptors"))
		assetRegistry.addParticleEmitterDescriptor(particleEmitterDescriptorData.at("id"), parseParticleEmitterDescriptor(particleEmitterDescriptorData));
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