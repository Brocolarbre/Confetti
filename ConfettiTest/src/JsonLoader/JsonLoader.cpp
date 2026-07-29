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
	std::string type = data["type"];

	if (type == "Attraction")
		return std::make_unique<cft::AttractionForceField>(data["spatialInfluence"].get<cft::SpatialInfluence>(), data["strength"]);
	else if (type == "Directional")
		return std::make_unique<cft::DirectionalForceField>(data["direction"].get<Vec3>().value, data["strength"]);
	else if (type == "Linear")
		return std::make_unique<cft::LinearDragForceField>(data["strength"]);
	else if (type == "Orbit")
		return std::make_unique<cft::OrbitForceField>(data["spatialInfluence"].get<cft::SpatialInfluence>(), data["axis"].get<Vec3>().value, data["strength"], data["radius"], data["radialCorrectionStrength"]);
	else if (type == "QuadraticDrag")
		return std::make_unique<cft::QuadraticDragForceField>(data["strength"]);
	else if (type == "Repulsion")
		return std::make_unique<cft::RepulsionForceField>(data["spatialInfluence"].get<cft::SpatialInfluence>(), data["strength"]);
	else if (type == "ShockWave")
		return std::make_unique<cft::ShockWaveForceField>(data["spatialInfluence"].get<cft::SpatialInfluence>(), data["axis"].get<Vec3>().value, data["speed"], data["strength"], data["thickness"]);
	else if (type == "Turbulence")
		return std::make_unique<cft::TurbulenceForceField>(data["strength"], data["seed"]);
	else if (type == "Vortex")
		return std::make_unique<cft::VortexForceField>(data["spatialInfluence"].get<cft::SpatialInfluence>(), data["axis"].get<Vec3>().value, data["strength"], data["pullStrength"]);
	else if (type == "Wind")
		return std::make_unique<cft::WindForceField>(data["direction"].get<Vec3>().value, data["strength"], data["drag"]);
	else
		throw std::runtime_error("Invalid force field type : '" + type + "'");
}

std::unique_ptr<cft::MotionBehavior> JsonLoader::parseMotionBehavior(const json& data)
{
	std::string type = data["type"];

	if (type == "Circle")
		return std::make_unique<cft::CircleMotionBehavior>(data["axis"].get<Vec3>().value, data["radius"], data["speed"]);
	else if (type == "FigureEight")
		return std::make_unique<cft::FigureEightMotionBehavior>(data["axis"].get<Vec3>().value, data["radius"], data["speed"]);
	else if (type == "Jitter")
		return std::make_unique<cft::JitterMotionBehavior>(data["strength"], data["seed"]);
	else if (type == "Orbit")
		return std::make_unique<cft::OrbitMotionBehavior>(data["origin"].get<Vec3>().value, data["axis"].get<Vec3>().value, data["radius"], data["speed"]);
	else if (type == "Oscillation")
		return std::make_unique<cft::OscillationMotionBehavior>(data["from"].get<Vec3>().value, data["to"].get<Vec3>().value, data["speed"]);
	else if (type == "Path")
		return std::make_unique<cft::PathMotionBehavior>(data["path"].get<std::vector<lw::Point>>(), data["interpolator"].get<std::unique_ptr<lw::Interpolator>>(), data["easing"].is_null() ? nullptr : data["easing"].get<std::unique_ptr<lw::Easing>>(), data["speed"]);
	else if (type == "Segment")
		return std::make_unique<cft::SegmentMotionBehavior>(data["from"].get<Vec3>().value, data["to"].get<Vec3>().value, data["speed"]);
	else if (type == "Spiral")
		return std::make_unique<cft::SpiralMotionBehavior>(data["origin"].get<Vec3>().value, data["axis"].get<Vec3>().value, data["startRadius"], data["growth"], data["speed"], data["rise"]);
	else
		throw std::runtime_error("Invalid motion behavior type : '" + type + "'");
}

std::unique_ptr<cft::VisualBehavior> JsonLoader::parseVisualBehavior(const json& data)
{
	std::string type = data["type"];

	if (type == "ColorShift")
		return std::make_unique<cft::ColorShiftVisualBehavior>(JsonTraits<cft::Color, Color>::readVector(data["colors"]), data["speed"], data["cyclic"]);
	if (type == "DimOut")
		return std::make_unique<cft::DimOutVisualBehavior>(data["duration"].get<cft::ParticleTime>());
	if (type == "FadeIn")
		return std::make_unique<cft::FadeInVisualBehavior>(data["duration"].get<cft::ParticleTime>());
	if (type == "FadeOut")
		return std::make_unique<cft::FadeOutVisualBehavior>(data["duration"].get<cft::ParticleTime>());
	if (type == "Flicker")
		return std::make_unique<cft::FlickerVisualBehavior>(data["minimumBrightness"], data["maximumBrightness"], data["speed"]);
	if (type == "GrowIn")
		return std::make_unique<cft::GrowInVisualBehavior>(data["duration"].get<cft::ParticleTime>());
	if (type == "Pulse")
		return std::make_unique<cft::PulseVisualBehavior>(data["colorA"].get<Color>().value, data["colorB"].get<Color>().value, data["speed"]);
	if (type == "ShrinkOut")
		return std::make_unique<cft::ShrinkOutVisualBehavior>(data["duration"].get<cft::ParticleTime>());
	if (type == "SmoothColorShift")
		return std::make_unique<cft::SmoothColorShiftVisualBehavior>(JsonTraits<cft::Color, Color>::readVector(data["colors"]), data["speed"], data["cyclic"]);
	if (type == "SquashStretch")
		return std::make_unique<cft::SquashStretchVisualBehavior>(data["strength"].get<Vec2>().value, data["speed"]);
	else
		throw std::runtime_error("Invalid visual behavior type : '" + type + "'");
}

std::unique_ptr<cft::ParticleSpawner> JsonLoader::parseParticleSpawner(const json& data)
{
	if (data.contains("spawnShape"))
	{
		return std::make_unique<cft::ParticleSpawner>(
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Color, Color>(data["colorAttributeGenerator"]),
			data["spawnShape"].get<std::unique_ptr<cft::SpawnShape>>(),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Rotation, Vec3>(data["rotationAttributeGenerator"]),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Scale, Vec3>(data["scaleAttributeGenerator"]),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::LinearVelocity, Vec3>(data["linearVelocityAttributeGenerator"]),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::AngularVelocity, Vec3>(data["angularVelocityAttributeGenerator"]),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Phase, float>(data["phaseAttributeGenerator"]),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Lifetime, float>(data["lifetimeAttributeGenerator"]),
			data["maximumParticleLifetime"]
		);
	}
	else
	{
		return std::make_unique<cft::ParticleSpawner>(
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Color, Color>(data["colorAttributeGenerator"]),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Position, Vec3>(data["positionAttributeGenerator"]),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Rotation, Vec3>(data["rotationAttributeGenerator"]),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Scale, Vec3>(data["scaleAttributeGenerator"]),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::LinearVelocity, Vec3>(data["linearVelocityAttributeGenerator"]),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::AngularVelocity, Vec3>(data["angularVelocityAttributeGenerator"]),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Phase, float>(data["phaseAttributeGenerator"]),
			JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Lifetime, float>(data["lifetimeAttributeGenerator"]),
			data["maximumParticleLifetime"]
		);
	}
}

std::unique_ptr<cft::EmissionPattern> JsonLoader::parseEmissionPattern(const json& data)
{
	std::string type = data["type"];

	if (type == "ConstantRate")
		return std::make_unique<cft::ConstantRateEmissionPattern>(data["rate"]);
	else if (type == "FixedBurst")
		return std::make_unique<cft::FixedBurstEmissionPattern>(data["count"], data["burstCount"], data["interval"]);
	else if (type == "LinearBurst")
		return std::make_unique<cft::LinearBurstEmissionPattern>(data["count"], data["initialInterval"], data["finalInterval"], data["transitionDuration"]);
	else if (type == "LinearRate")
		return std::make_unique<cft::LinearRateEmissionPattern>(data["initialRate"], data["finalRate"], data["transitionDuration"]);
	else if (type == "PeriodicBurst")
		return std::make_unique<cft::PeriodicBurstEmissionPattern>(data["count"], data["interval"]);
	else if (type == "RandomRate")
		return std::make_unique<cft::RandomRateEmissionPattern>(data["minimumRate"], data["maximumRate"], data["seed"]);
	else if (type == "SingleBurst")
		return std::make_unique<cft::SingleBurstEmissionPattern>(data["count"]);
	else
		throw std::runtime_error("Invalid emission pattern type : '" + type + "'");
}

std::unique_ptr<cft::ParticleLinker> JsonLoader::parseParticleLinker(const json& data)
{
	std::string type = data["type"];

	std::vector<std::unique_ptr<cft::LinkRule>> connectionRules = data["connectionRules"].get<std::vector<std::unique_ptr<cft::LinkRule>>>();
	std::vector<std::unique_ptr<cft::LinkRule>> validationRules = data["validationRules"].get<std::vector<std::unique_ptr<cft::LinkRule>>>();

	if (type == "Chain")
		return std::make_unique<cft::ChainParticleLinker>(std::move(connectionRules), std::move(validationRules));
	else if (type == "KNearestNeighbor")
		return std::make_unique<cft::KNearestNeighborParticleLinker>(std::move(connectionRules), std::move(validationRules), data["neighborCount"]);
	else if (type == "NearestNeighbor")
		return std::make_unique<cft::NearestNeighborParticleLinker>(std::move(connectionRules), std::move(validationRules));
	else if (type == "Origin")
		return std::make_unique<cft::OriginParticleLinker>(std::move(connectionRules), std::move(validationRules), data["origin"].get<Vec3>().value);
	else if (type == "Random")
		return std::make_unique<cft::RandomParticleLinker>(std::move(connectionRules), std::move(validationRules), data["connectionCount"], data["seed"]);
	else if (type == "Target")
		return std::make_unique<cft::TargetParticleLinker>(std::move(connectionRules), std::move(validationRules), data["targetParticleId"]);
	else
		throw std::runtime_error("Invalid particle linker type : '" + type + "'");
}

std::unique_ptr<cft::RibbonGenerator> JsonLoader::parseRibbonGenerator(const json& data)
{
	std::string type = data["type"];

	if (type == "Path")
		return std::make_unique<cft::PathRibbonGenerator>(data["path"].get<std::vector<lw::Point>>(), data["interpolator"].get<std::unique_ptr<lw::Interpolator>>(), data["easing"].is_null() ? nullptr : data["easing"].get<std::unique_ptr<lw::Easing>>());
	else if (type == "Segment")
		return std::make_unique<cft::SegmentRibbonGenerator>();
	else if (type == "Spiral")
		return std::make_unique<cft::SpiralRibbonGenerator>(data["frequency"], data["radius"], data["animationSpeed"]);
	else if (type == "Wave")
		return std::make_unique<cft::WaveRibbonGenerator>(data["frequency"], data["amplitude"], data["animationSpeed"]);
	else
		throw std::runtime_error("Invalid ribbon generator type : '" + type + "'");
}

cft::Image JsonLoader::parseImage(const json& data)
{
	cft::Image image;
	image.loadFromFile(data["path"]);

	return image;
}

cft::Model JsonLoader::parseModel(const json& data)
{
	cft::Model model;
	model.loadFromFile(data["path"]);

	return model;
}

cft::SpriteSheetDescriptor JsonLoader::parseSpriteSheetDescriptor(const json& data)
{
	return cft::SpriteSheetDescriptor{
		data["imageId"],
		data["frameCount"],
		data["rowFrameCount"],
		data["frameWidth"],
		data["frameHeight"],
		data["animationSpeed"]
	};
}

cft::ParticleEffectDescriptor JsonLoader::parseParticleEffectDescriptor(const json& data)
{
	return cft::ParticleEffectDescriptor{
		data["emitterSpawnContexts"].get<std::vector<cft::ParticleEmitterSpawnContext>>()
	};
}

cft::ParticleEmitterDescriptor JsonLoader::parseParticleEmitterDescriptor(const json& data)
{
	return cft::ParticleEmitterDescriptor{
		data["poolId"],
		data["particleSpawnerId"],
		data["emissionPatternId"],
		data["trailConfiguration"].is_null() ? std::nullopt : std::make_optional<cft::TrailConfiguration>(data["trailConfiguration"].get<cft::TrailConfiguration>()),
		data["ribbonConfiguration"].is_null() ? std::nullopt : std::make_optional<cft::RibbonConfiguration>(data["ribbonConfiguration"].get<cft::RibbonConfiguration>()),
		data["spawnTriggerDescriptor"].is_null() ? std::nullopt : std::make_optional<cft::SpawnTriggerDescriptor>(data["spawnTriggerDescriptor"].get<cft::SpawnTriggerDescriptor>()),
		data["renderConfiguration"].get<cft::RenderConfiguration>(),
		data["forceFieldIds"].get<std::vector<unsigned int>>(),
		data["motionBehaviorIds"].get<std::vector<unsigned int>>(),
		data["visualBehaviorIds"].get<std::vector<unsigned int>>()
	};
}

void JsonLoader::loadAssets(const json& data, cft::AssetRegistry& assetRegistry)
{
	for (const auto& forceFieldData : data["forceFields"])
		assetRegistry.addForceField(forceFieldData["id"], parseForceField(forceFieldData));

	for (const auto& motionBehaviorData : data["motionBehaviors"])
		assetRegistry.addMotionBehavior(motionBehaviorData["id"], parseMotionBehavior(motionBehaviorData));

	for (const auto& visualBehaviorData : data["visualBehaviors"])
		assetRegistry.addVisualBehavior(visualBehaviorData["id"], parseVisualBehavior(visualBehaviorData));

	for (const auto& particleSpawnerData : data["particleSpawners"])
		assetRegistry.addParticleSpawner(particleSpawnerData["id"], parseParticleSpawner(particleSpawnerData));

	for (const auto& emissionPatternData : data["emissionPatterns"])
		assetRegistry.addEmissionPattern(emissionPatternData["id"], parseEmissionPattern(emissionPatternData));

	for (const auto& particleLinkerData : data["particleLinkers"])
		assetRegistry.addParticleLinker(particleLinkerData["id"], parseParticleLinker(particleLinkerData));

	for (const auto& ribbonGeneratorData : data["ribbonGenerators"])
		assetRegistry.addRibbonGenerator(ribbonGeneratorData["id"], parseRibbonGenerator(ribbonGeneratorData));

	for (const auto& imageData : data["images"])
		assetRegistry.addImage(imageData["id"], parseImage(imageData));

	for (const auto& modelData : data["models"])
		assetRegistry.addModel(modelData["id"], parseModel(modelData));

	for (const auto& spriteSheetDescriptorData : data["spriteSheetDescriptors"])
		assetRegistry.addSpriteSheetDescriptor(spriteSheetDescriptorData["id"], parseSpriteSheetDescriptor(spriteSheetDescriptorData));

	for (const auto& particleEffectDescriptorData : data["particleEffectDescriptors"])
		assetRegistry.addParticleEffectDescriptor(particleEffectDescriptorData["id"], parseParticleEffectDescriptor(particleEffectDescriptorData));

	for (const auto& particleEmitterDescriptorData : data["particleEmitterDescriptors"])
		assetRegistry.addParticleEmitterDescriptor(particleEmitterDescriptorData["id"], parseParticleEmitterDescriptor(particleEmitterDescriptorData));
}

void JsonLoader::loadBillboardRendererTextures(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry)
{
	unsigned int width = data["width"];
	unsigned int height = data["height"];

	std::vector<unsigned int> imageIds;
	imageIds.reserve(data["imageIds"].size());

	for (const auto& imageId : data["imageIds"])
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

	particleSimulation.setSeed(data["seed"]);

	loadAssets(data["assets"], assetRegistry);

	loadBillboardRendererTextures(data["billboardRendererImages"], particleRenderer, assetRegistry);
	loadMeshRendererTextures(data["meshRendererImageIds"], particleRenderer, assetRegistry);
	loadMeshRendererMeshes(data["meshRendererModelIds"], particleRenderer, assetRegistry);
}