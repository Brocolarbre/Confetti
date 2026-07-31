#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonTraits.hpp"

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

namespace cft
{
	void JsonLoader::registerTypes(JsonFactory<VisualBehavior>& factory, const ProviderRegistry& providerRegistry)
	{
		factory.registerType("ColorShift", [](const json& data) { return std::make_unique<ColorShiftVisualBehavior>(JsonTraits<Color, JsonTypes::Color>::readVector(data.at("colors")), data.at("speed"), data.at("cyclic")); });
		factory.registerType("DimOut", [](const json& data) { return std::make_unique<DimOutVisualBehavior>(data.at("duration").get<ParticleTime>()); });
		factory.registerType("FadeIn", [](const json& data) { return std::make_unique<FadeInVisualBehavior>(data.at("duration").get<ParticleTime>()); });
		factory.registerType("FadeOut", [](const json& data) { return std::make_unique<FadeOutVisualBehavior>(data.at("duration").get<ParticleTime>()); });
		factory.registerType("Flicker", [](const json& data) { return std::make_unique<FlickerVisualBehavior>(data.at("minimumBrightness"), data.at("maximumBrightness"), data.at("speed")); });
		factory.registerType("GrowIn", [](const json& data) { return std::make_unique<GrowInVisualBehavior>(data.at("duration").get<ParticleTime>()); });
		factory.registerType("Pulse", [](const json& data) { return std::make_unique<PulseVisualBehavior>(data.at("colorA").get<JsonTypes::Color>().value, data.at("colorB").get<JsonTypes::Color>().value, data.at("speed")); });
		factory.registerType("ShrinkOut", [](const json& data) { return std::make_unique<ShrinkOutVisualBehavior>(data.at("duration").get<ParticleTime>()); });
		factory.registerType("SmoothColorShift", [](const json& data) { return std::make_unique<SmoothColorShiftVisualBehavior>(JsonTraits<Color, JsonTypes::Color>::readVector(data.at("colors")), data.at("speed"), data.at("cyclic")); });
		factory.registerType("SquashStretch", [](const json& data) { return std::make_unique<SquashStretchVisualBehavior>(data.at("strength").get<JsonTypes::Vec2>().value, data.at("speed")); });
	}
}