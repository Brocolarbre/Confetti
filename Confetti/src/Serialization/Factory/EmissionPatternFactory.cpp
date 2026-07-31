#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonSerialization.hpp"

#include <Confetti/Emission/EmissionPattern/ConstantRateEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/FixedBurstEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/LinearBurstEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/LinearRateEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/PeriodicBurstEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/RandomRateEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/SingleBurstEmissionPattern.hpp>

namespace cft
{
	void JsonLoader::registerTypes(JsonFactory<cft::EmissionPattern>& factory, const ProviderRegistry& providerRegistry)
	{
		factory.registerType("ConstantRate", [](const json& data) { return std::make_unique<cft::ConstantRateEmissionPattern>(data.at("rate")); });
		factory.registerType("FixedBurst", [](const json& data) { return std::make_unique<cft::FixedBurstEmissionPattern>(data.at("count"), data.at("burstCount"), data.at("interval")); });
		factory.registerType("LinearBurst", [](const json& data) { return std::make_unique<cft::LinearBurstEmissionPattern>(data.at("count"), data.at("initialInterval"), data.at("finalInterval"), data.at("transitionDuration")); });
		factory.registerType("LinearRate", [](const json& data) { return std::make_unique<cft::LinearRateEmissionPattern>(data.at("initialRate"), data.at("finalRate"), data.at("transitionDuration")); });
		factory.registerType("PeriodicBurst", [](const json& data) { return std::make_unique<cft::PeriodicBurstEmissionPattern>(data.at("count"), data.at("interval")); });
		factory.registerType("RandomRate", [](const json& data) { return std::make_unique<cft::RandomRateEmissionPattern>(data.at("minimumRate"), data.at("maximumRate"), data.at("seed")); });
		factory.registerType("SingleBurst", [](const json& data) { return std::make_unique<cft::SingleBurstEmissionPattern>(data.at("count")); });
	}
}