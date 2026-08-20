#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonSerialization.hpp"

#include "Confetti/Emission/SpawnShape/CircleSpawnShape.hpp"
#include "Confetti/Emission/SpawnShape/ConeSpawnShape.hpp"
#include "Confetti/Emission/SpawnShape/ConeVolumeSpawnShape.hpp"
#include "Confetti/Emission/SpawnShape/CylinderSpawnShape.hpp"
#include "Confetti/Emission/SpawnShape/CylinderVolumeSpawnShape.hpp"
#include "Confetti/Emission/SpawnShape/DiskSpawnShape.hpp"
#include "Confetti/Emission/SpawnShape/GalaxyDiskSpawnShape.hpp"
#include "Confetti/Emission/SpawnShape/SphereSpawnShape.hpp"
#include "Confetti/Emission/SpawnShape/SphereVolumeSpawnShape.hpp"
#include "Confetti/Emission/SpawnShape/SpiralSpawnShape.hpp"

namespace cft
{
	void JsonLoader::registerTypes(JsonFactory<SpawnShape>& factory, const ProviderRegistry& providerRegistry)
	{
		factory.registerType("Circle", [](const json& data) { return std::make_unique<CircleSpawnShape>(data.at("radius"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("Cone", [](const json& data) { return std::make_unique<ConeSpawnShape>(data.at("height"), data.at("radius"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("ConeVolume", [](const json& data) { return std::make_unique<ConeVolumeSpawnShape>(data.at("height"), data.at("radius"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("Cylinder", [](const json& data) { return std::make_unique<CylinderSpawnShape>(data.at("height"), data.at("radius"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("CylinderVolume", [](const json& data) { return std::make_unique<CylinderVolumeSpawnShape>(data.at("height"), data.at("radius"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("Disk", [](const json& data) { return std::make_unique<DiskSpawnShape>(data.at("radius"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("GalaxyDisk", [](const json& data) { return std::make_unique<GalaxyDiskSpawnShape>(data.at("radius"), data.at("bulgeRadius"), data.at("thickness"), data.at("arms"), data.at("turns"), data.at("armSpread"), data.at("axis").get<JsonTypes::Vec3>().value); });
		factory.registerType("Sphere", [](const json& data) { return std::make_unique<SphereSpawnShape>(data.at("radius")); });
		factory.registerType("SphereVolume", [](const json& data) { return std::make_unique<SphereVolumeSpawnShape>(data.at("radius")); });
		factory.registerType("Spiral", [](const json& data) { return std::make_unique<SpiralSpawnShape>(data.at("height"), data.at("radius"), data.at("turns"), data.at("helix"), data.at("axis").get<JsonTypes::Vec3>().value); });
	}
}