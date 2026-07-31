#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonSerialization.hpp"

#include <Confetti/Emission/SpawnShape/CircleSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/ConeSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/ConeVolumeSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/CylinderSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/CylinderVolumeSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/DiskSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/SphereSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/SphereVolumeSpawnShape.hpp>

namespace cft
{
	void JsonLoader::registerTypes(JsonFactory<cft::SpawnShape>& factory, const ProviderRegistry& providerRegistry)
	{
		factory.registerType("Circle", [](const json& data) { return std::make_unique<cft::CircleSpawnShape>(data.at("radius"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("Cone", [](const json& data) { return std::make_unique<cft::ConeSpawnShape>(data.at("height"), data.at("radius"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("ConeVolume", [](const json& data) { return std::make_unique<cft::ConeVolumeSpawnShape>(data.at("height"), data.at("radius"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("Cylinder", [](const json& data) { return std::make_unique<cft::CylinderSpawnShape>(data.at("height"), data.at("radius"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("CylinderVolume", [](const json& data) { return std::make_unique<cft::CylinderVolumeSpawnShape>(data.at("height"), data.at("radius"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("Disk", [](const json& data) { return std::make_unique<cft::DiskSpawnShape>(data.at("radius"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("Sphere", [](const json& data) { return std::make_unique<cft::SphereSpawnShape>(data.at("radius")); });
		factory.registerType("SphereVolume", [](const json& data) { return std::make_unique<cft::SphereVolumeSpawnShape>(data.at("radius")); });
	}
}