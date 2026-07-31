#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonSerialization.hpp"

#include <Confetti/Behavior/Force/AttractionForceField.hpp>
#include <Confetti/Behavior/Force/DirectionalForceField.hpp>
#include <Confetti/Behavior/Force/FollowTargetForceField.hpp>
#include <Confetti/Behavior/Force/LinearDragForceField.hpp>
#include <Confetti/Behavior/Force/OrbitForceField.hpp>
#include <Confetti/Behavior/Force/QuadraticDragForceField.hpp>
#include <Confetti/Behavior/Force/RepulsionForceField.hpp>
#include <Confetti/Behavior/Force/ShockWaveForceField.hpp>
#include <Confetti/Behavior/Force/TurbulenceForceField.hpp>
#include <Confetti/Behavior/Force/VortexForceField.hpp>
#include <Confetti/Behavior/Force/WindForceField.hpp>

namespace cft
{
	void JsonLoader::registerTypes(JsonFactory<cft::ForceField>& factory, const ProviderRegistry& providerRegistry)
	{
		factory.registerType("Attraction", [](const json& data) { return std::make_unique<cft::AttractionForceField>(data.at("spatialInfluence").get<cft::SpatialInfluence>(), data.at("strength")); });
		factory.registerType("Directional", [](const json& data) { return std::make_unique<cft::DirectionalForceField>(data.at("direction").get<JsonTypes::Vec3>().value, data.at("strength")); });
		factory.registerType("FollowTarget", [&providerRegistry](const json& data) { return std::make_unique<cft::FollowTargetForceField>(providerRegistry.getProvider<glm::vec3>(data.at("targetProvider")), data.at("responseTime"), data.at("dampingRatio")); });
		factory.registerType("LinearDrag", [](const json& data) { return std::make_unique<cft::LinearDragForceField>(data.at("strength")); });
		factory.registerType("Orbit", [](const json& data) { return std::make_unique<cft::OrbitForceField>(data.at("spatialInfluence").get<cft::SpatialInfluence>(), data.at("axis").get<JsonTypes::Vec3>().value, data.at("strength"), data.at("radius"), data.at("radialCorrectionStrength")); });
		factory.registerType("QuadraticDrag", [](const json& data) { return std::make_unique<cft::QuadraticDragForceField>(data.at("strength")); });
		factory.registerType("Repulsion", [](const json& data) { return std::make_unique<cft::RepulsionForceField>(data.at("spatialInfluence").get<cft::SpatialInfluence>(), data.at("strength")); });
		factory.registerType("ShockWave", [](const json& data) { return std::make_unique<cft::ShockWaveForceField>(data.at("spatialInfluence").get<cft::SpatialInfluence>(), data.at("axis").get<JsonTypes::Vec3>().value, data.at("speed"), data.at("strength"), data.at("thickness")); });
		factory.registerType("Turbulence", [](const json& data) { return std::make_unique<cft::TurbulenceForceField>(data.at("strength"), data.at("seed")); });
		factory.registerType("Vortex", [](const json& data) { return std::make_unique<cft::VortexForceField>(data.at("spatialInfluence").get<cft::SpatialInfluence>(), data.at("axis").get<JsonTypes::Vec3>().value, data.at("strength"), data.at("pullStrength")); });
		factory.registerType("Wind", [](const json& data) { return std::make_unique<cft::WindForceField>(data.at("direction").get<JsonTypes::Vec3>().value, data.at("strength"), data.at("drag")); });
	}
}