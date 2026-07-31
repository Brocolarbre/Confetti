#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonSerialization.hpp"

#include <Confetti/Behavior/Motion/CircleMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/FigureEightMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/JitterMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/OrbitMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/OscillationMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/PathMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/SegmentMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/SnapTargetMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/SpiralMotionBehavior.hpp>

namespace cft
{
	void JsonLoader::registerTypes(JsonFactory<MotionBehavior>& factory, const ProviderRegistry& providerRegistry)
	{
		factory.registerType("Circle", [](const json& data) { return std::make_unique<CircleMotionBehavior>(data.at("axis").get<JsonTypes::Vec3>().value, data.at("radius"), data.at("speed")); });
		factory.registerType("FigureEight", [](const json& data) { return std::make_unique<FigureEightMotionBehavior>(data.at("axis").get<JsonTypes::Vec3>().value, data.at("radius"), data.at("speed")); });
		factory.registerType("Jitter", [](const json& data) { return std::make_unique<JitterMotionBehavior>(data.at("strength"), data.at("seed")); });
		factory.registerType("Orbit", [](const json& data) { return std::make_unique<OrbitMotionBehavior>(data.at("origin").get<JsonTypes::Vec3>().value, data.at("axis").get<JsonTypes::Vec3>().value, data.at("radius"), data.at("speed")); });
		factory.registerType("Oscillation", [](const json& data) { return std::make_unique<OscillationMotionBehavior>(data.at("from").get<JsonTypes::Vec3>().value, data.at("to").get<JsonTypes::Vec3>().value, data.at("speed")); });
		factory.registerType("Path", [](const json& data) { return std::make_unique<PathMotionBehavior>(data.at("path").get<std::vector<lw::Point>>(), data.at("interpolator").get<std::unique_ptr<lw::Interpolator>>(), JsonTools::parseOptionalPointer<lw::Easing>(data.at("easing")), data.at("speed")); });
		factory.registerType("Segment", [](const json& data) { return std::make_unique<SegmentMotionBehavior>(data.at("from").get<JsonTypes::Vec3>().value, data.at("to").get<JsonTypes::Vec3>().value, data.at("speed")); });
		factory.registerType("SnapTarget", [&providerRegistry](const json& data) { return std::make_unique<SnapTargetMotionBehavior>(providerRegistry.getProvider<glm::vec3>(data.at("targetProvider"))); });
		factory.registerType("Spiral", [](const json& data) { return std::make_unique<SpiralMotionBehavior>(data.at("origin").get<JsonTypes::Vec3>().value, data.at("axis").get<JsonTypes::Vec3>().value, data.at("startRadius"), data.at("growth"), data.at("speed"), data.at("rise")); });
	}
}