#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonSerialization.hpp"

#include "Confetti/Simulation/Link/RibbonGenerator/PathRibbonGenerator.hpp"
#include "Confetti/Simulation/Link/RibbonGenerator/SegmentRibbonGenerator.hpp"
#include "Confetti/Simulation/Link/RibbonGenerator/SpiralRibbonGenerator.hpp"
#include "Confetti/Simulation/Link/RibbonGenerator/WaveRibbonGenerator.hpp"

namespace cft
{
	void JsonLoader::registerTypes(JsonFactory<RibbonGenerator>& factory, const ProviderRegistry& providerRegistry)
	{
		factory.registerType("Path", [](const json& data) { return std::make_unique<PathRibbonGenerator>(data.at("path").get<std::vector<lw::Point>>(), data.at("interpolator").get<std::unique_ptr<lw::Interpolator>>(), JsonTools::parseOptionalPointer<lw::Easing>(data.at("easing"))); });
		factory.registerType("Segment", [](const json& data) { return std::make_unique<SegmentRibbonGenerator>(); });
		factory.registerType("Spiral", [](const json& data) { return std::make_unique<SpiralRibbonGenerator>(data.at("frequency"), data.at("radius"), data.at("animationSpeed")); });
		factory.registerType("Wave", [](const json& data) { return std::make_unique<WaveRibbonGenerator>(data.at("frequency"), data.at("amplitude"), data.at("animationSpeed")); });
	}
}