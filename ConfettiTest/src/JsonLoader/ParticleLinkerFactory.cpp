#include "JsonLoader.hpp"
#include "JsonSerialization.hpp"

#include <Confetti/Simulation/Link/ParticleLinker/ChainParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/KNearestNeighborParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/NearestNeighborParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/OriginParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/RandomParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/TargetParticleLinker.hpp>

void JsonLoader::registerTypes(JsonFactory<cft::ParticleLinker>& factory)
{
	factory.registerType("Chain", [](const json& data) { return std::make_unique<cft::ChainParticleLinker>(std::move(data.at("connectionRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>()), std::move(data.at("validationRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>())); });
	factory.registerType("KNearestNeighbor", [](const json& data) { return std::make_unique<cft::KNearestNeighborParticleLinker>(std::move(data.at("connectionRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>()), std::move(data.at("validationRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>()), data.at("neighborCount")); });
	factory.registerType("NearestNeighbor", [](const json& data) { return std::make_unique<cft::NearestNeighborParticleLinker>(std::move(data.at("connectionRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>()), std::move(data.at("validationRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>())); });
	factory.registerType("Origin", [](const json& data) { return std::make_unique<cft::OriginParticleLinker>(std::move(data.at("connectionRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>()), std::move(data.at("validationRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>()), data.at("origin").get<Vec3>().value); });
	factory.registerType("Random", [](const json& data) { return std::make_unique<cft::RandomParticleLinker>(std::move(data.at("connectionRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>()), std::move(data.at("validationRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>()), data.at("connectionCount"), data.at("seed")); });
	factory.registerType("Target", [](const json& data) { return std::make_unique<cft::TargetParticleLinker>(std::move(data.at("connectionRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>()), std::move(data.at("validationRules").get<std::vector<std::unique_ptr<cft::LinkRule>>>()), data.at("targetParticleId")); });
}