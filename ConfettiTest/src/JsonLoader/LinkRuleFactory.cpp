#include "JsonLoader.hpp"
#include "JsonSerialization.hpp"

#include <Confetti/Simulation/Link/LinkRule/AgeSimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/ColorSimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/ConnectionLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/DistanceLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/PhaseSimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/VelocitySimilarityLinkRule.hpp>

void JsonLoader::registerTypes(JsonFactory<cft::LinkRule>& factory)
{
	factory.registerType("AgeSimilarity", [](const json& data) { return std::make_unique<cft::AgeSimilarityLinkRule>(data.at("threshold")); });
	factory.registerType("ColorSimilarity", [](const json& data) { return std::make_unique<cft::ColorSimilarityLinkRule>(data.at("threshold")); });
	factory.registerType("Connection", [](const json& data) { return std::make_unique<cft::ConnectionLinkRule>(data.at("maximumConnectionCount")); });
	factory.registerType("Distance", [](const json& data) { return std::make_unique<cft::DistanceLinkRule>(data.at("minimumDistance"), data.at("maximumDistance")); });
	factory.registerType("PhaseSimilarity", [](const json& data) { return std::make_unique<cft::PhaseSimilarityLinkRule>(data.at("threshold")); });
	factory.registerType("VelocitySimilarity", [](const json& data) { return std::make_unique<cft::VelocitySimilarityLinkRule>(data.at("threshold")); });
}