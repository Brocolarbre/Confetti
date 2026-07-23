#include "JsonLoader.hpp"

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

#include <Confetti/Emission/ParticleSpawner.hpp>

#include <Confetti/Emission/AttributeGenerator/BinaryAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/UnaryAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/ConstantAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/InterpolatedRandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/LinearAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/RandomAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/RandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/WeightedRandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/NormalBurstLinearVelocityGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/NormalLinearVelocityGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/RandomNormalOffsetPositionGenerator.hpp>

#include <Confetti/Emission/SpawnShape/CircleSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/ConeSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/ConeVolumeSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/CylinderSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/CylinderVolumeSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/DiskSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/SphereSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/SphereVolumeSpawnShape.hpp>

#include <Confetti/Emission/EmissionPattern/ConstantRateEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/FixedBurstEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/LinearBurstEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/LinearRateEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/PeriodicBurstEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/RandomRateEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/SingleBurstEmissionPattern.hpp>

#include <Confetti/Simulation/Link/LinkRule/AgeSimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/ColorSimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/ConnectionLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/DistanceLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/PhaseSimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/VelocitySimilarityLinkRule.hpp>

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

#include <LineWeaver/Interpolation/BezierInterpolator.hpp>
#include <LineWeaver/Interpolation/BSplineInterpolator.hpp>
#include <LineWeaver/Interpolation/CatmullRomInterpolator.hpp>
#include <LineWeaver/Interpolation/HermiteInterpolator.hpp>
#include <LineWeaver/Interpolation/LinearInterpolator.hpp>

#include <LineWeaver/Easing/EaseCurve.hpp>
#include <LineWeaver/Easing/EaseInBack.hpp>
#include <LineWeaver/Easing/EaseInBounce.hpp>
#include <LineWeaver/Easing/EaseInCircular.hpp>
#include <LineWeaver/Easing/EaseInCubic.hpp>
#include <LineWeaver/Easing/EaseInElastic.hpp>
#include <LineWeaver/Easing/EaseInExponential.hpp>
#include <LineWeaver/Easing/EaseInOutBack.hpp>
#include <LineWeaver/Easing/EaseInOutBounce.hpp>
#include <LineWeaver/Easing/EaseInOutCircular.hpp>
#include <LineWeaver/Easing/EaseInOutCubic.hpp>
#include <LineWeaver/Easing/EaseInOutElastic.hpp>
#include <LineWeaver/Easing/EaseInOutExponential.hpp>
#include <LineWeaver/Easing/EaseInOutQuadratic.hpp>
#include <LineWeaver/Easing/EaseInOutQuartic.hpp>
#include <LineWeaver/Easing/EaseInOutQuintic.hpp>
#include <LineWeaver/Easing/EaseInOutSine.hpp>
#include <LineWeaver/Easing/EaseInQuadratic.hpp>
#include <LineWeaver/Easing/EaseInQuartic.hpp>
#include <LineWeaver/Easing/EaseInQuintic.hpp>
#include <LineWeaver/Easing/EaseInSine.hpp>
#include <LineWeaver/Easing/EaseLinear.hpp>
#include <LineWeaver/Easing/EaseOutBack.hpp>
#include <LineWeaver/Easing/EaseOutBounce.hpp>
#include <LineWeaver/Easing/EaseOutCircular.hpp>
#include <LineWeaver/Easing/EaseOutCubic.hpp>
#include <LineWeaver/Easing/EaseOutElastic.hpp>
#include <LineWeaver/Easing/EaseOutExponential.hpp>
#include <LineWeaver/Easing/EaseOutQuadratic.hpp>
#include <LineWeaver/Easing/EaseOutQuartic.hpp>
#include <LineWeaver/Easing/EaseOutQuintic.hpp>
#include <LineWeaver/Easing/EaseOutSine.hpp>
#include <LineWeaver/Easing/EaseSmootherstep.hpp>
#include <LineWeaver/Easing/EaseSmoothstep.hpp>

#include <fstream>
#include <stdexcept>

glm::vec4 JsonLoader::parseColor(const json& data)
{
	return glm::vec4(data["r"], data["g"], data["b"], data["a"]);
}

glm::vec3 JsonLoader::parseVec3(const json& data)
{
	return glm::vec3(data["x"], data["y"], data["z"]);
}

glm::vec2 JsonLoader::parseVec2(const json& data)
{
	return glm::vec2(data["x"], data["y"]);
}

lw::Point JsonLoader::parsePoint(const json& data)
{
	return lw::Point(data["x"], data["y"], data["z"]);
}

std::unique_ptr<cft::SpawnShape> JsonLoader::parseSpawnShape(const json& data)
{
	std::string type = data["type"];

	if (type == "Circle")
		return std::make_unique<cft::CircleSpawnShape>(data["radius"], parseVec3(data["axis"]));
	else if (type == "Cone")
		return std::make_unique<cft::ConeSpawnShape>(data["height"], data["radius"], parseVec3(data["axis"]));
	else if (type == "ConeVolume")
		return std::make_unique<cft::ConeVolumeSpawnShape>(data["height"], data["radius"], parseVec3(data["axis"]));
	else if (type == "Cylinder")
		return std::make_unique<cft::CylinderSpawnShape>(data["height"], data["radius"], parseVec3(data["axis"]));
	else if (type == "CylinderVolume")
		return std::make_unique<cft::CylinderVolumeSpawnShape>(data["height"], data["radius"], parseVec3(data["axis"]));
	else if (type == "Disk")
		return std::make_unique<cft::DiskSpawnShape>(data["radius"], parseVec3(data["axis"]));
	else if (type == "Sphere")
		return std::make_unique<cft::SphereSpawnShape>(data["radius"]);
	else if (type == "SphereVolume")
		return std::make_unique<cft::SphereVolumeSpawnShape>(data["radius"]);
	else
		throw std::runtime_error("Invalid spanw shape type : '" + type + "'");
}

/*
enum class AttributeType
{
	Color,
	Position,
	Rotation,
	Scale,
	LinearVelocity,
	AngularVelocity,
	Phase,
	Lifetime
};

template <typename T, typename U>
cft::BinaryAttributeGenerator<T, U> parseBinaryAttributeGenerator(const json& data)
{
	if (type == "Binary")
		return std::make_unique<cft::BinaryAttributeGenerator<T>>();
	if (type == "Unary")
		return std::make_unique<cft::UnaryAttributeGenerator<T>>();
}
*/

cft::Falloff JsonLoader::parseFalloff(const json& data)
{
	if (data == "Constant")
		return cft::Falloff::Constant;
	else if (data == "Linear")
		return cft::Falloff::Linear;
	else if (data == "Quadratic")
		return cft::Falloff::Quadratic;
	else if (data == "Cubic")
		return cft::Falloff::Cubic;
	else
		throw std::runtime_error("Invalid falloff type : '" + std::string(data) + "'");
}

cft::SpatialInfluence JsonLoader::parseSpatialInfluence(const json& data)
{
	return cft::SpatialInfluence(parseVec3(data["origin"]), data["radius"], parseFalloff(data["falloff"]));
}

std::unique_ptr<lw::Interpolator> JsonLoader::parseInterpolator(const json& data)
{
	std::string type = data["type"];

	if (type == "Bezier")
		return std::make_unique<lw::BezierInterpolator>(data["pointsPerSegment"]);
	else if (type == "BSpline")
		return std::make_unique<lw::BSplineInterpolator>(parseInterpolator(data["interpolator"]));
	else if (type == "CatmullRom")
		return std::make_unique<lw::CatmullRomInterpolator>();
	else if (type == "Hermite")
		return std::make_unique<lw::HermiteInterpolator>();
	else if (type == "Linear")
		return std::make_unique<lw::LinearInterpolator>();
	else
		throw std::runtime_error("Invalid interpolator type : '" + type + "'");
}

std::unique_ptr<lw::Easing> JsonLoader::parseEasing(const json& data)
{
	std::string type = data["type"];

	if (type == "Curve")
		return std::make_unique<lw::EaseCurve>(parseInterpolator(data["interpolator"]), parseArray<lw::Point>(data["path"], parsePoint));
	else if (type == "InBack")
		return std::make_unique<lw::EaseInBack>();
	else if (type == "InBounce")
		return std::make_unique<lw::EaseInBounce>();
	else if (type == "InCircular")
		return std::make_unique<lw::EaseInCircular>();
	else if (type == "InCubic")
		return std::make_unique<lw::EaseInCubic>();
	else if (type == "InElastic")
		return std::make_unique<lw::EaseInElastic>();
	else if (type == "InExponential")
		return std::make_unique<lw::EaseInExponential>();
	else if (type == "InOutBack")
		return std::make_unique<lw::EaseInOutBack>();
	else if (type == "InOutBounce")
		return std::make_unique<lw::EaseInOutBounce>();
	else if (type == "InOutCircular")
		return std::make_unique<lw::EaseInOutCircular>();
	else if (type == "InOutCubic")
		return std::make_unique<lw::EaseInOutCubic>();
	else if (type == "InOutElastic")
		return std::make_unique<lw::EaseInOutElastic>();
	else if (type == "InOutExponential")
		return std::make_unique<lw::EaseInOutExponential>();
	else if (type == "InOutQuadratic")
		return std::make_unique<lw::EaseInOutQuadratic>();
	else if (type == "InOutQuartic")
		return std::make_unique<lw::EaseInOutQuartic>();
	else if (type == "InOutQuintic")
		return std::make_unique<lw::EaseInOutQuintic>();
	else if (type == "InOutSine")
		return std::make_unique<lw::EaseInOutSine>();
	else if (type == "InQuadratic")
		return std::make_unique<lw::EaseInQuadratic>();
	else if (type == "InQuartic")
		return std::make_unique<lw::EaseInQuartic>();
	else if (type == "InQuintic")
		return std::make_unique<lw::EaseInQuintic>();
	else if (type == "InSine")
		return std::make_unique<lw::EaseInSine>();
	else if (type == "Linear")
		return std::make_unique<lw::EaseLinear>();
	else if (type == "OutBack")
		return std::make_unique<lw::EaseOutBack>();
	else if (type == "OutBounce")
		return std::make_unique<lw::EaseOutBounce>();
	else if (type == "OutCircular")
		return std::make_unique<lw::EaseOutCircular>();
	else if (type == "OutCubic")
		return std::make_unique<lw::EaseOutCubic>();
	else if (type == "OutElastic")
		return std::make_unique<lw::EaseOutElastic>();
	else if (type == "OutExponential")
		return std::make_unique<lw::EaseOutExponential>();
	else if (type == "OutQuadratic")
		return std::make_unique<lw::EaseOutQuadratic>();
	else if (type == "OutQuartic")
		return std::make_unique<lw::EaseOutQuartic>();
	else if (type == "OutQuintic")
		return std::make_unique<lw::EaseOutQuintic>();
	else if (type == "OutSine")
		return std::make_unique<lw::EaseOutSine>();
	else if (type == "Smootherstep")
		return std::make_unique<lw::EaseSmootherstep>();
	else if (type == "Smoothstep")
		return std::make_unique<lw::EaseSmoothstep>();
	else
		throw std::runtime_error("Invalid easing type : '" + type + "'");
}

cft::ParticleTime::Space JsonLoader::parseParticleTimeSpace(const json& data)
{
	if (data == "Absolute")
		return cft::ParticleTime::Space::Absolute;
	else if (data == "Normalized")
		return cft::ParticleTime::Space::Normalized;
	else
		throw std::runtime_error("Invalid particle time space type : '" + std::string(data) + "'");
}

cft::ParticleTime JsonLoader::parseParticleTime(const json& data)
{
	return cft::ParticleTime{
		data["value"],
		parseParticleTimeSpace(data["space"])
	};
}

std::unique_ptr<cft::LinkRule> JsonLoader::parseLinkRule(const json& data)
{
	std::string type = data["type"];

	if (type == "AgeSimilarity")
		return std::make_unique<cft::AgeSimilarityLinkRule>(data["threshold"]);
	else if (type == "ColorSimilarity")
		return std::make_unique<cft::ColorSimilarityLinkRule>(data["threshold"]);
	else if (type == "Connection")
		return std::make_unique<cft::ConnectionLinkRule>(data["maximumConnectionCount"]);
	else if (type == "Distance")
		return std::make_unique<cft::DistanceLinkRule>(data["minimumDistance"], data["maximumDistance"]);
	else if (type == "PhaseSimilarity")
		return std::make_unique<cft::PhaseSimilarityLinkRule>(data["threshold"]);
	else if (type == "VelocitySimilarity")
		return std::make_unique<cft::VelocitySimilarityLinkRule>(data["threshold"]);
	else
		throw std::runtime_error("Invalid link rule type : '" + type + "'");
}

cft::ThicknessEvolutionDistribution JsonLoader::parseThicknessEvolutionDistribution(const json& data)
{
	if (data == "Constant")
		return cft::ThicknessEvolutionDistribution::Constant;
	else if (data == "Linear")
		return cft::ThicknessEvolutionDistribution::Linear;
	else if (data == "Quadratic")
		return cft::ThicknessEvolutionDistribution::Quadratic;
	else
		throw std::runtime_error("Invalid thickness distribution type : '" + std::string(data) + "'");
}

cft::LifetimeFade JsonLoader::parseLifetimeFade(const json& data)
{
	return cft::LifetimeFade{
		data["start"],
		data["end"]
	};
}

cft::ColorInterpolation JsonLoader::parseColorInterpolation(const json& data)
{
	if (data == "Constant")
		return cft::ColorInterpolation::Constant;
	else if (data == "Linear")
		return cft::ColorInterpolation::Linear;
	else
		throw std::runtime_error("Invalid color interpolation type : '" + std::string(data) + "'");
}

cft::ThicknessDistribution JsonLoader::parseThicknessDistribution(const json& data)
{
	if (data == "Linear")
		return cft::ThicknessDistribution::Linear;
	else if (data == "Quadratic")
		return cft::ThicknessDistribution::Quadratic;
	else
		throw std::runtime_error("Invalid thickness distribution type : '" + std::string(data) + "'");
}

cft::ThicknessEvolution JsonLoader::parseThicknessEvolution(const json& data)
{
	return cft::ThicknessEvolution{
		parseThicknessEvolutionDistribution(data["distribution"]),
		data["speed"]
	};
}

cft::PathImage JsonLoader::parsePathImage(const json& data)
{
	return cft::PathImage{
		data["imageId"],
		data["repeatStretch"].is_null() ? std::nullopt : std::make_optional<float>(data["repeatStretch"])
	};
}

cft::PeriodicSpawnTriggerContext JsonLoader::parsePeriodicTriggerSpawnContext(const json& data)
{
	return cft::PeriodicSpawnTriggerContext{
		parseParticleEmitterSpawnContext(data["emitterSpawnContext"]),
		data["interval"]
	};
}

cft::ParticleEmitterSpawnContext JsonLoader::parseParticleEmitterSpawnContext(const json& data)
{
	return cft::ParticleEmitterSpawnContext{
		data["emitterDescriptorId"],
		parseTimeRange(data["timeRange"]),
		parseMotionState(data["initialMotionState"]),
		parseArray<unsigned int>(data["forceFieldIds"], parseValue<unsigned int>),
		parseArray<unsigned int>(data["motionBehaviorIds"], parseValue<unsigned int>)
	};
}

cft::PathConfiguration JsonLoader::parsePathConfiguration(const json& data)
{
	return cft::PathConfiguration{
		data["startThickness"],
		data["endThickness"],
		data["lifetime"].is_null() ? std::nullopt : std::make_optional<float>(data["lifetime"]),
		data["lifetimeFade"].is_null() ? std::nullopt : std::make_optional<cft::LifetimeFade>(parseLifetimeFade(data["lifetimeFade"])),
		data["appendParticleColor"],
		parseArray<glm::vec4>(data["colorGradient"], parseColor),
		data["colorStart"].is_null() ? std::nullopt : std::make_optional<std::vector<float>>(parseArray<float>(data["colorStart"], parseValue<float>)),
		parseColorInterpolation(data["colorInterpolation"]),
		parseThicknessDistribution(data["thicknessDistribution"]),
		data["thicknessEvolution"].is_null() ? std::nullopt : std::make_optional<cft::ThicknessEvolution>(parseThicknessEvolution(data["thicknessEvolution"])),
		data["pathImage"].is_null() ? std::nullopt : std::make_optional<cft::PathImage>(parsePathImage(data["pathImage"]))
	};
}

cft::TrailConfiguration JsonLoader::parseTrailConfiguration(const json& data)
{
	return cft::TrailConfiguration{
		data["persistenceLifetime"],
		data["minimumSpawnDistance"],
		data["maximumSpawnTime"].is_null() ? std::nullopt : std::make_optional<float>(data["maximumSpawnTime"]),
		data["maximumSegmentCount"].is_null() ? std::nullopt : std::make_optional<unsigned int>(data["maximumSegmentCount"]),
		parsePathConfiguration(data["pathConfiguration"])
	};
}

cft::RibbonConfiguration JsonLoader::parseRibbonConfiguration(const json& data)
{
	return cft::RibbonConfiguration{
		parsePathConfiguration(data["pathConfiguration"]),
		data["particleLinkerId"],
		data["ribbonGeneratorId"],
		data["ribbonPointCount"]
	};
}

cft::TimeRange JsonLoader::parseTimeRange(const json& data)
{
	return cft::TimeRange{
		data["spawnTime"],
		data["duration"]
	};
}

cft::MotionState JsonLoader::parseMotionState(const json& data)
{
	glm::vec3 eulerAngles = parseVec3(data["rotation"]);
	glm::quat rotation = glm::quat(glm::vec3(glm::radians(eulerAngles.x), glm::radians(eulerAngles.y), glm::radians(eulerAngles.z)));

	return cft::MotionState{
		parseVec3(data["position"]),
		parseVec3(data["linearVelocity"]),
		rotation,
		parseVec3(data["angularVelocity"])
	};
}

cft::SpawnTriggerDescriptor JsonLoader::parseSpawnTriggerDescriptor(const json& data)
{
	return cft::SpawnTriggerDescriptor{
		data["maximumRecursionDepth"],
		data["spawnEmitterSpawnContext"].is_null() ? std::nullopt : std::make_optional<cft::ParticleEmitterSpawnContext>(parseParticleEmitterSpawnContext(data["spawnEmitterSpawnContext"])),
		data["deathEmitterSpawnContext"].is_null() ? std::nullopt : std::make_optional<cft::ParticleEmitterSpawnContext>(parseParticleEmitterSpawnContext(data["deathEmitterSpawnContext"])),
		data["periodicEmitterSpawnContext"].is_null() ? std::nullopt : std::make_optional<cft::PeriodicSpawnTriggerContext>(parsePeriodicTriggerSpawnContext(data["periodicEmitterSpawnContext"]))
	};
}

cft::RenderType JsonLoader::parseRenderType(const json& data)
{
	if (data == "Billboard")
		return cft::RenderType::Billboard;
	else if (data == "Mesh")
		return cft::RenderType::Mesh;
	else
		throw std::runtime_error("Invalid render type : '" + std::string(data) + "'");
}

cft::RenderConfiguration JsonLoader::parseRenderConfiguration(const json& data)
{
	cft::RenderType renderType = parseRenderType(data["renderType"]);
	std::variant<cft::BillboardRenderConfiguration, cft::MeshRenderConfiguration> configurationData;
	switch (renderType)
	{
	case cft::RenderType::Billboard:
		configurationData = parseBillboardRenderConfiguration(data["configurationData"]);
		break;
	case cft::RenderType::Mesh:
		configurationData = parseMeshRenderConfiguration(data["configurationData"]);
		break;
	}

	return cft::RenderConfiguration{
		renderType,
		configurationData
	};
}

cft::BillboardRenderConfiguration JsonLoader::parseBillboardRenderConfiguration(const json& data)
{
	return cft::BillboardRenderConfiguration{
		data["spriteSheetId"].is_null() ? std::nullopt : std::make_optional<unsigned int>(data["spriteSheetId"])
	};
}

cft::MeshRenderConfiguration JsonLoader::parseMeshRenderConfiguration(const json& data)
{
	return cft::MeshRenderConfiguration{
		data["modelId"],
		data["imageId"].is_null() ? std::nullopt : std::make_optional<unsigned int>(data["imageId"])
	};
}

std::unique_ptr<cft::ForceField> JsonLoader::parseForceField(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Attraction")
		return std::make_unique<cft::AttractionForceField>(parseSpatialInfluence(data["spatialInfluence"]), data["strength"]);
	else if (type == "Directional")
		return std::make_unique<cft::DirectionalForceField>(parseVec3(data["direction"]), data["strength"]);
	else if (type == "Linear")
		return std::make_unique<cft::LinearDragForceField>(data["strength"]);
	else if (type == "Orbit")
		return std::make_unique<cft::OrbitForceField>(parseSpatialInfluence(data["spatialInfluence"]), parseVec3(data["axis"]), data["strength"], data["radius"], data["radialCorrectionStrength"]);
	else if (type == "QuadraticDrag")
		return std::make_unique<cft::QuadraticDragForceField>(data["strength"]);
	else if (type == "Repulsion")
		return std::make_unique<cft::RepulsionForceField>(parseSpatialInfluence(data["spatialInfluence"]), data["strength"]);
	else if (type == "ShockWave")
		return std::make_unique<cft::ShockWaveForceField>(parseSpatialInfluence(data["spatialInfluence"]), parseVec3(data["axis"]), data["speed"], data["strength"], data["thickness"]);
	else if (type == "Turbulence")
		return std::make_unique<cft::TurbulenceForceField>(data["strength"], randomNumberGenerator);
	else if (type == "Vortex")
		return std::make_unique<cft::VortexForceField>(parseSpatialInfluence(data["spatialInfluence"]), parseVec3(data["axis"]), data["strength"], data["pullStrength"]);
	else if (type == "Wind")
		return std::make_unique<cft::WindForceField>(parseVec3(data["direction"]), data["strength"], data["drag"]);
	else
		throw std::runtime_error("Invalid force field type : '" + type + "'");
}

std::unique_ptr<cft::MotionBehavior> JsonLoader::parseMotionBehavior(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Circle")
		return std::make_unique<cft::CircleMotionBehavior>(parseVec3(data["axis"]), data["radius"], data["speed"]);
	else if (type == "FigureEight")
		return std::make_unique<cft::FigureEightMotionBehavior>(parseVec3(data["axis"]), data["radius"], data["speed"]);
	else if (type == "Jitter")
		return std::make_unique<cft::JitterMotionBehavior>(data["strength"], randomNumberGenerator);
	else if (type == "Orbit")
		return std::make_unique<cft::OrbitMotionBehavior>(parseVec3(data["origin"]), parseVec3(data["axis"]), data["radius"], data["speed"]);
	else if (type == "Oscillation")
		return std::make_unique<cft::OscillationMotionBehavior>(parseVec3(data["from"]), parseVec3(data["to"]), data["speed"]);
	else if (type == "Path")
		return std::make_unique<cft::PathMotionBehavior>(parseArray<lw::Point>(data["path"], parsePoint), parseInterpolator(data["interpolator"]), data["easing"].is_null() ? nullptr : parseEasing(data["easing"]), data["speed"]);
	else if (type == "Segment")
		return std::make_unique<cft::SegmentMotionBehavior>(parseVec3(data["from"]), parseVec3(data["to"]), data["speed"]);
	else if (type == "Spiral")
		return std::make_unique<cft::SpiralMotionBehavior>(parseVec3(data["origin"]), parseVec3(data["axis"]), data["startRadius"], data["growth"], data["speed"], data["rise"]);
	else
		throw std::runtime_error("Invalid motion behavior type : '" + type + "'");
}

std::unique_ptr<cft::VisualBehavior> JsonLoader::parseVisualBehavior(const json& data)
{
	std::string type = data["type"];

	if (type == "ColorShift")
		return std::make_unique<cft::ColorShiftVisualBehavior>(parseArray<glm::vec4>(data["colors"], parseColor), data["speed"], data["cyclic"]);
	if (type == "DimOut")
		return std::make_unique<cft::DimOutVisualBehavior>(parseParticleTime(data["duration"]));
	if (type == "FadeIn")
		return std::make_unique<cft::FadeInVisualBehavior>(parseParticleTime(data["duration"]));
	if (type == "FadeOut")
		return std::make_unique<cft::FadeOutVisualBehavior>(parseParticleTime(data["duration"]));
	if (type == "Flicker")
		return std::make_unique<cft::FlickerVisualBehavior>(data["minimumBrightness"], data["maximumBrightness"], data["speed"]);
	if (type == "GrowIn")
		return std::make_unique<cft::GrowInVisualBehavior>(parseParticleTime(data["duration"]));
	if (type == "Pulse")
		return std::make_unique<cft::PulseVisualBehavior>(parseColor(data["colorA"]), parseColor(data["colorB"]), data["speed"]);
	if (type == "ShrinkOut")
		return std::make_unique<cft::ShrinkOutVisualBehavior>(parseParticleTime(data["duration"]));
	if (type == "SmoothColorShift")
		return std::make_unique<cft::SmoothColorShiftVisualBehavior>(parseArray<glm::vec4>(data["colors"], parseColor), data["speed"], data["cyclic"]);
	if (type == "SquashStretch")
		return std::make_unique<cft::SquashStretchVisualBehavior>(parseVec2(data["strength"]), data["speed"]);
	else
		throw std::runtime_error("Invalid visual behavior type : '" + type + "'");
}

std::unique_ptr<cft::ParticleSpawner> JsonLoader::parseParticleSpawner(const json& data)
{
	data["colorAttributeGenerator"]

	return std::unique_ptr<cft::ParticleSpawner>();
}

std::unique_ptr<cft::EmissionPattern> JsonLoader::parseEmissionPattern(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
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
		return std::make_unique<cft::RandomRateEmissionPattern>(data["minimumRate"], data["maximumRate"], randomNumberGenerator);
	else if (type == "SingleBurst")
		return std::make_unique<cft::SingleBurstEmissionPattern>(data["count"]);
	else
		throw std::runtime_error("Invalid emission pattern type : '" + type + "'");
}

std::unique_ptr<cft::ParticleLinker> JsonLoader::parseParticleLinker(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	std::vector<std::unique_ptr<cft::LinkRule>> connectionRules = parseArray<std::unique_ptr<cft::LinkRule>>(data["connectionRules"], parseLinkRule);
	std::vector<std::unique_ptr<cft::LinkRule>> validationRules = parseArray<std::unique_ptr<cft::LinkRule>>(data["validationRules"], parseLinkRule);

	if (type == "Chain")
		return std::make_unique<cft::ChainParticleLinker>(std::move(connectionRules), std::move(validationRules));
	else if (type == "KNearestNeighbor")
		return std::make_unique<cft::KNearestNeighborParticleLinker>(std::move(connectionRules), std::move(validationRules), data["neighborCount"]);
	else if (type == "NearestNeighbor")
		return std::make_unique<cft::NearestNeighborParticleLinker>(std::move(connectionRules), std::move(validationRules));
	else if (type == "Origin")
		return std::make_unique<cft::OriginParticleLinker>(std::move(connectionRules), std::move(validationRules), parseVec3(data["origin"]));
	else if (type == "Random")
		return std::make_unique<cft::RandomParticleLinker>(std::move(connectionRules), std::move(validationRules), data["connectionCount"], randomNumberGenerator);
	else if (type == "Target")
		return std::make_unique<cft::TargetParticleLinker>(std::move(connectionRules), std::move(validationRules), data["targetParticleId"]);
	else
		throw std::runtime_error("Invalid particle linker type : '" + type + "'");
}

std::unique_ptr<cft::RibbonGenerator> JsonLoader::parseRibbonGenerator(const json& data)
{
	std::string type = data["type"];

	if (type == "Path")
		return std::make_unique<cft::PathRibbonGenerator>(parseArray<lw::Point>(data["path"], parsePoint), parseInterpolator(data["interpolator"]), data["easing"].is_null() ? nullptr : parseEasing(data["easing"]));
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
		parseArray<cft::ParticleEmitterSpawnContext>(data["emitterSpawnContexts"], parseParticleEmitterSpawnContext)
	};
}

cft::ParticleEmitterDescriptor JsonLoader::parseParticleEmitterDescriptor(const json& data)
{
	return cft::ParticleEmitterDescriptor{
		data["poolId"],
		data["particleSpawnerId"],
		data["emissionPatternId"],
		data["trailConfiguration"].is_null() ? std::nullopt : std::make_optional<cft::TrailConfiguration>(parseTrailConfiguration(data["trailConfiguration"])),
		data["ribbonConfiguration"].is_null() ? std::nullopt : std::make_optional<cft::RibbonConfiguration>(parseRibbonConfiguration(data["ribbonConfiguration"])),
		data["spawnTriggerDescriptor"].is_null() ? std::nullopt : std::make_optional<cft::SpawnTriggerDescriptor>(parseSpawnTriggerDescriptor(data["spawnTriggerDescriptor"])),
		parseRenderConfiguration(data["renderConfiguration"]),
		parseArray<unsigned int>(data["forceFieldIds"], parseValue<unsigned int>),
		parseArray<unsigned int>(data["motionBehaviorIds"], parseValue<unsigned int>),
		parseArray<unsigned int>(data["visualBehaviorIds"], parseValue<unsigned int>)
	};
}

void JsonLoader::load(const std::string& path, cft::AssetRegistry& assetRegistry, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::ifstream file(path);
	json data = json::parse(file);

	for (const auto& forceFieldData : data["forceFields"])
		assetRegistry.addForceField(forceFieldData["id"], parseForceField(forceFieldData, randomNumberGenerator));

	for (const auto& motionBehaviorData : data["motionBehaviors"])
		assetRegistry.addMotionBehavior(motionBehaviorData["id"], parseMotionBehavior(motionBehaviorData, randomNumberGenerator));

	for (const auto& visualBehaviorData : data["visualBehaviors"])
		assetRegistry.addVisualBehavior(visualBehaviorData["id"], parseVisualBehavior(visualBehaviorData));

	for (const auto& particleSpawnerData : data["particleSpawners"])
		assetRegistry.addParticleSpawner(particleSpawnerData["id"], parseParticleSpawner(particleSpawnerData));

	for (const auto& emissionPatternData : data["emissionPatterns"])
		assetRegistry.addEmissionPattern(emissionPatternData["id"], parseEmissionPattern(emissionPatternData, randomNumberGenerator));

	for (const auto& particleLinkerData : data["particleLinkers"])
		assetRegistry.addParticleLinker(particleLinkerData["id"], parseParticleLinker(particleLinkerData, randomNumberGenerator));

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