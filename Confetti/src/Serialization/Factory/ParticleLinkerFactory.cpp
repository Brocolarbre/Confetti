#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonSerialization.hpp"

#include <Confetti/Simulation/Link/ParticleLinker/ChainParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/KNearestNeighborParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/NearestNeighborParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/OriginParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/RandomParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/TargetParticleLinker.hpp>

namespace cft
{
	void JsonLoader::registerTypes(JsonFactory<ParticleLinker>& factory, const ProviderRegistry& providerRegistry)
	{
		factory.registerType("Chain", [](const json& data) { return std::make_unique<ChainParticleLinker>(std::move(data.at("connectionRules").get<std::vector<std::unique_ptr<LinkRule>>>()), std::move(data.at("validationRules").get<std::vector<std::unique_ptr<LinkRule>>>())); });
		factory.registerType("KNearestNeighbor", [](const json& data) { return std::make_unique<KNearestNeighborParticleLinker>(std::move(data.at("connectionRules").get<std::vector<std::unique_ptr<LinkRule>>>()), std::move(data.at("validationRules").get<std::vector<std::unique_ptr<LinkRule>>>()), data.at("neighborCount")); });
		factory.registerType("NearestNeighbor", [](const json& data) { return std::make_unique<NearestNeighborParticleLinker>(std::move(data.at("connectionRules").get<std::vector<std::unique_ptr<LinkRule>>>()), std::move(data.at("validationRules").get<std::vector<std::unique_ptr<LinkRule>>>())); });
		factory.registerType("Origin", [](const json& data) { return std::make_unique<OriginParticleLinker>(std::move(data.at("connectionRules").get<std::vector<std::unique_ptr<LinkRule>>>()), std::move(data.at("validationRules").get<std::vector<std::unique_ptr<LinkRule>>>()), data.at("origin").get<JsonTypes::Vec3>().value); });
		factory.registerType("Random", [](const json& data) { return std::make_unique<RandomParticleLinker>(std::move(data.at("connectionRules").get<std::vector<std::unique_ptr<LinkRule>>>()), std::move(data.at("validationRules").get<std::vector<std::unique_ptr<LinkRule>>>()), data.at("connectionCount"), data.at("seed")); });
		factory.registerType("Target", [](const json& data) { return std::make_unique<TargetParticleLinker>(std::move(data.at("connectionRules").get<std::vector<std::unique_ptr<LinkRule>>>()), std::move(data.at("validationRules").get<std::vector<std::unique_ptr<LinkRule>>>()), data.at("targetParticleId")); });
	}
}