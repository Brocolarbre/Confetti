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

std::unique_ptr<cft::AttributeGenerator<cft::Color>> JsonLoader::parseColorAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Constant")
		return std::make_unique<cft::ConstantAttributeGenerator<cft::Color>>(data["value"].get<Color>().value);
	else if (type == "InterpolatedRandomSet")
		return std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Color>>(wrapperToType<cft::Color>(data["values"].get<std::vector<Color>>()), randomNumberGenerator);
	else if (type == "Linear")
		return std::make_unique<cft::LinearAttributeGenerator<cft::Color>>(data["from"].get<Color>().value, data["to"].get<Color>().value);
	else if (type == "Random")
			return std::make_unique<cft::RandomAttributeGenerator<cft::Color>>(data["minimum"].get<Color>().value, data["maximum"].get<Color>().value, randomNumberGenerator);
	else if (type == "RandomSet")
		return std::make_unique<cft::RandomSetAttributeGenerator<cft::Color>>(wrapperToType<cft::Color>(data["values"].get<std::vector<Color>>()), randomNumberGenerator);
	else if (type == "WeightedRandomSet")
		return std::make_unique<cft::WeightedRandomSetAttributeGenerator<cft::Color>>(wrapperToType<cft::Color>(data["values"].get<std::vector<cft::WeightedValue<Color>>>()), randomNumberGenerator);
	else
		throw std::runtime_error("Invalid attribute generator type : '" + type + "'");
}

std::unique_ptr<cft::AttributeGenerator<cft::Position>> JsonLoader::parsePositionAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Constant")
		return std::make_unique<cft::ConstantAttributeGenerator<cft::Position>>(data["value"].get<Vec3>().value);
	else if (type == "InterpolatedRandomSet")
		return std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Position>>(wrapperToType<cft::Position>(data["values"].get<std::vector<Vec3>>()), randomNumberGenerator);
	else if (type == "Linear")
		return std::make_unique<cft::LinearAttributeGenerator<cft::Position>>(data["from"].get<Vec3>().value, data["to"].get<Vec3>().value);
	else if (type == "Random")
		return std::make_unique<cft::RandomAttributeGenerator<cft::Position>>(data["minimum"].get<Vec3>().value, data["maximum"].get<Vec3>().value, randomNumberGenerator);
	else if (type == "RandomSet")
		return std::make_unique<cft::RandomSetAttributeGenerator<cft::Position>>(wrapperToType<cft::Position>(data["values"].get<std::vector<Vec3>>()), randomNumberGenerator);
	else if (type == "WeightedRandomSet")
		return std::make_unique<cft::WeightedRandomSetAttributeGenerator<cft::Position>>(wrapperToType<cft::Position>(data["values"].get<std::vector<cft::WeightedValue<Vec3>>>()), randomNumberGenerator);
	else
		throw std::runtime_error("Invalid attribute generator type : '" + type + "'");
}

std::unique_ptr<cft::AttributeGenerator<cft::Rotation>> JsonLoader::parseRotationAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Constant")
		return std::make_unique<cft::ConstantAttributeGenerator<cft::Rotation>>(eulerAnglesToQuaternion(data["value"].get<Vec3>().value));
	else if (type == "InterpolatedRandomSet")
		return std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Rotation>>(eulerAnglesToQuaternion(wrapperToType<glm::vec3>(data["values"].get<std::vector<Vec3>>())), randomNumberGenerator);
	else if (type == "Linear")
		return std::make_unique<cft::LinearAttributeGenerator<cft::Rotation>>(eulerAnglesToQuaternion(data["from"].get<Vec3>().value), eulerAnglesToQuaternion(data["to"].get<Vec3>().value));
	else if (type == "Random")
		return std::make_unique<cft::RandomAttributeGenerator<cft::Rotation>>(eulerAnglesToQuaternion(data["minimum"].get<Vec3>().value), eulerAnglesToQuaternion(data["maximum"].get<Vec3>().value), randomNumberGenerator);
	else if (type == "RandomSet")
		return std::make_unique<cft::RandomSetAttributeGenerator<cft::Rotation>>(eulerAnglesToQuaternion(wrapperToType<glm::vec3>(data["values"].get<std::vector<Vec3>>())), randomNumberGenerator);
	else if (type == "WeightedRandomSet")
		return std::make_unique<cft::WeightedRandomSetAttributeGenerator<cft::Rotation>>(eulerAnglesToQuaternion(wrapperToType<glm::vec3>(data["values"].get<std::vector<cft::WeightedValue<Vec3>>>())), randomNumberGenerator);
	else
		throw std::runtime_error("Invalid attribute generator type : '" + type + "'");
}

std::unique_ptr<cft::AttributeGenerator<cft::Scale>> JsonLoader::parseScaleAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Constant")
		return std::make_unique<cft::ConstantAttributeGenerator<cft::Scale>>(data["value"].get<Vec3>().value);
	else if (type == "InterpolatedRandomSet")
		return std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Scale>>(wrapperToType<cft::Scale>(data["values"].get<std::vector<Vec3>>()), randomNumberGenerator);
	else if (type == "Linear")
		return std::make_unique<cft::LinearAttributeGenerator<cft::Scale>>(data["from"].get<Vec3>().value, data["to"].get<Vec3>().value);
	else if (type == "Random")
		return std::make_unique<cft::RandomAttributeGenerator<cft::Scale>>(data["minimum"].get<Vec3>().value, data["maximum"].get<Vec3>().value, randomNumberGenerator);
	else if (type == "RandomSet")
		return std::make_unique<cft::RandomSetAttributeGenerator<cft::Scale>>(wrapperToType<cft::Scale>(data["values"].get<std::vector<Vec3>>()), randomNumberGenerator);
	else if (type == "WeightedRandomSet")
		return std::make_unique<cft::WeightedRandomSetAttributeGenerator<cft::Scale>>(wrapperToType<cft::Scale>(data["values"].get<std::vector<cft::WeightedValue<Vec3>>>()), randomNumberGenerator);
	else
		throw std::runtime_error("Invalid attribute generator type : '" + type + "'");
}

std::unique_ptr<cft::AttributeGenerator<cft::LinearVelocity>> JsonLoader::parseLinearVelocityAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Constant")
		return std::make_unique<cft::ConstantAttributeGenerator<cft::LinearVelocity>>(data["value"].get<Vec3>().value);
	else if (type == "InterpolatedRandomSet")
		return std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::LinearVelocity>>(wrapperToType<cft::LinearVelocity>(data["values"].get<std::vector<Vec3>>()), randomNumberGenerator);
	else if (type == "Linear")
		return std::make_unique<cft::LinearAttributeGenerator<cft::LinearVelocity>>(data["from"].get<Vec3>().value, data["to"].get<Vec3>().value);
	else if (type == "Random")
		return std::make_unique<cft::RandomAttributeGenerator<cft::LinearVelocity>>(data["minimum"].get<Vec3>().value, data["maximum"].get<Vec3>().value, randomNumberGenerator);
	else if (type == "RandomSet")
		return std::make_unique<cft::RandomSetAttributeGenerator<cft::LinearVelocity>>(wrapperToType<cft::LinearVelocity>(data["values"].get<std::vector<Vec3>>()), randomNumberGenerator);
	else if (type == "WeightedRandomSet")
		return std::make_unique<cft::WeightedRandomSetAttributeGenerator<cft::LinearVelocity>>(wrapperToType<cft::LinearVelocity>(data["values"].get<std::vector<cft::WeightedValue<Vec3>>>()), randomNumberGenerator);
	else
		throw std::runtime_error("Invalid attribute generator type : '" + type + "'");
}

std::unique_ptr<cft::AttributeGenerator<cft::AngularVelocity>> JsonLoader::parseAngularVelocityAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Constant")
		return std::make_unique<cft::ConstantAttributeGenerator<cft::AngularVelocity>>(data["value"].get<Vec3>().value);
	else if (type == "InterpolatedRandomSet")
		return std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::AngularVelocity>>(wrapperToType<cft::AngularVelocity>(data["values"].get<std::vector<Vec3>>()), randomNumberGenerator);
	else if (type == "Linear")
		return std::make_unique<cft::LinearAttributeGenerator<cft::AngularVelocity>>(data["from"].get<Vec3>().value, data["to"].get<Vec3>().value);
	else if (type == "Random")
		return std::make_unique<cft::RandomAttributeGenerator<cft::AngularVelocity>>(data["minimum"].get<Vec3>().value, data["maximum"].get<Vec3>().value, randomNumberGenerator);
	else if (type == "RandomSet")
		return std::make_unique<cft::RandomSetAttributeGenerator<cft::AngularVelocity>>(wrapperToType<cft::AngularVelocity>(data["values"].get<std::vector<Vec3>>()), randomNumberGenerator);
	else if (type == "WeightedRandomSet")
		return std::make_unique<cft::WeightedRandomSetAttributeGenerator<cft::AngularVelocity>>(wrapperToType<cft::AngularVelocity>(data["values"].get<std::vector<cft::WeightedValue<Vec3>>>()), randomNumberGenerator);
	else
		throw std::runtime_error("Invalid attribute generator type : '" + type + "'");
}

std::unique_ptr<cft::AttributeGenerator<cft::Phase>> JsonLoader::parsePhaseAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Constant")
		return std::make_unique<cft::ConstantAttributeGenerator<cft::Phase>>(data["value"]);
	else if (type == "InterpolatedRandomSet")
		return std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Phase>>(data["values"].get<std::vector<float>>(), randomNumberGenerator);
	else if (type == "Linear")
		return std::make_unique<cft::LinearAttributeGenerator<cft::Phase>>(data["from"], data["to"]);
	else if (type == "Random")
		return std::make_unique<cft::RandomAttributeGenerator<cft::Phase>>(data["minimum"], data["maximum"], randomNumberGenerator);
	else if (type == "RandomSet")
		return std::make_unique<cft::RandomSetAttributeGenerator<cft::Phase>>(data["values"].get<std::vector<float>>(), randomNumberGenerator);
	else if (type == "WeightedRandomSet")
		return std::make_unique<cft::WeightedRandomSetAttributeGenerator<cft::Phase>>(data["values"].get<std::vector<cft::WeightedValue<float>>>(), randomNumberGenerator);
	else
		throw std::runtime_error("Invalid attribute generator type : '" + type + "'");
}

std::unique_ptr<cft::AttributeGenerator<cft::Lifetime>> JsonLoader::parseLifetimeAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Constant")
		return std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(data["value"]);
	else if (type == "InterpolatedRandomSet")
		return std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Lifetime>>(data["values"].get<std::vector<float>>(), randomNumberGenerator);
	else if (type == "Linear")
		return std::make_unique<cft::LinearAttributeGenerator<cft::Lifetime>>(data["from"], data["to"]);
	else if (type == "Random")
		return std::make_unique<cft::RandomAttributeGenerator<cft::Lifetime>>(data["minimum"], data["maximum"], randomNumberGenerator);
	else if (type == "RandomSet")
		return std::make_unique<cft::RandomSetAttributeGenerator<cft::Lifetime>>(data["values"].get<std::vector<float>>(), randomNumberGenerator);
	else if (type == "WeightedRandomSet")
		return std::make_unique<cft::WeightedRandomSetAttributeGenerator<cft::Lifetime>>(data["values"].get<std::vector<cft::WeightedValue<float>>>(), randomNumberGenerator);
	else
		throw std::runtime_error("Invalid attribute generator type : '" + type + "'");
}

std::unique_ptr<cft::ForceField> JsonLoader::parseForceField(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
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
		return std::make_unique<cft::TurbulenceForceField>(data["strength"], randomNumberGenerator);
	else if (type == "Vortex")
		return std::make_unique<cft::VortexForceField>(data["spatialInfluence"].get<cft::SpatialInfluence>(), data["axis"].get<Vec3>().value, data["strength"], data["pullStrength"]);
	else if (type == "Wind")
		return std::make_unique<cft::WindForceField>(data["direction"].get<Vec3>().value, data["strength"], data["drag"]);
	else
		throw std::runtime_error("Invalid force field type : '" + type + "'");
}

std::unique_ptr<cft::MotionBehavior> JsonLoader::parseMotionBehavior(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Circle")
		return std::make_unique<cft::CircleMotionBehavior>(data["axis"].get<Vec3>().value, data["radius"], data["speed"]);
	else if (type == "FigureEight")
		return std::make_unique<cft::FigureEightMotionBehavior>(data["axis"].get<Vec3>().value, data["radius"], data["speed"]);
	else if (type == "Jitter")
		return std::make_unique<cft::JitterMotionBehavior>(data["strength"], randomNumberGenerator);
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
		return std::make_unique<cft::ColorShiftVisualBehavior>(wrapperToType<glm::vec4>(data["colors"].get<std::vector<Color>>()), data["speed"], data["cyclic"]);
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
		return std::make_unique<cft::SmoothColorShiftVisualBehavior>(wrapperToType<glm::vec4>(data["colors"].get<std::vector<Color>>()), data["speed"], data["cyclic"]);
	if (type == "SquashStretch")
		return std::make_unique<cft::SquashStretchVisualBehavior>(data["strength"].get<Vec2>().value, data["speed"]);
	else
		throw std::runtime_error("Invalid visual behavior type : '" + type + "'");
}

std::unique_ptr<cft::ParticleSpawner> JsonLoader::parseParticleSpawner(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	if (data.contains("spawnShape"))
	{
		return std::make_unique<cft::ParticleSpawner>(
			parseColorAttributeGenerator(data["colorAttributeGenerator"], randomNumberGenerator),
			data["spawnShape"].get<std::unique_ptr<cft::SpawnShape>>(),
			parseRotationAttributeGenerator(data["rotationAttributeGenerator"], randomNumberGenerator),
			parseScaleAttributeGenerator(data["scaleAttributeGenerator"], randomNumberGenerator),
			parseLinearVelocityAttributeGenerator(data["linearVelocityAttributeGenerator"], randomNumberGenerator),
			parseAngularVelocityAttributeGenerator(data["angularVelocityAttributeGenerator"], randomNumberGenerator),
			parsePhaseAttributeGenerator(data["phaseAttributeGenerator"], randomNumberGenerator),
			parseLifetimeAttributeGenerator(data["lifetimeAttributeGenerator"], randomNumberGenerator),
			data["maximumParticleLifetime"]
		);
	}
	else
	{
		return std::make_unique<cft::ParticleSpawner>(
			parseColorAttributeGenerator(data["colorAttributeGenerator"], randomNumberGenerator),
			parsePositionAttributeGenerator(data["positionAttributeGenerator"], randomNumberGenerator),
			parseRotationAttributeGenerator(data["rotationAttributeGenerator"], randomNumberGenerator),
			parseScaleAttributeGenerator(data["scaleAttributeGenerator"], randomNumberGenerator),
			parseLinearVelocityAttributeGenerator(data["linearVelocityAttributeGenerator"], randomNumberGenerator),
			parseAngularVelocityAttributeGenerator(data["angularVelocityAttributeGenerator"], randomNumberGenerator),
			parsePhaseAttributeGenerator(data["phaseAttributeGenerator"], randomNumberGenerator),
			parseLifetimeAttributeGenerator(data["lifetimeAttributeGenerator"], randomNumberGenerator),
			data["maximumParticleLifetime"]
		);
	}
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
		assetRegistry.addParticleSpawner(particleSpawnerData["id"], parseParticleSpawner(particleSpawnerData, randomNumberGenerator));

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