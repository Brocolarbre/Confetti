#include "JsonLoader.hpp"
#include "JsonSerialization.hpp"

#include <Confetti/Behavior/Motion/CircleMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/FigureEightMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/JitterMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/OrbitMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/OscillationMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/PathMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/SegmentMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/SpiralMotionBehavior.hpp>

void JsonLoader::registerTypes(JsonFactory<cft::MotionBehavior>& factory)
{
	factory.registerType("Circle", [](const json& data) { return std::make_unique<cft::CircleMotionBehavior>(data.at("axis").get<Vec3>().value, data.at("radius"), data.at("speed")); });
	factory.registerType("FigureEight", [](const json& data) { return std::make_unique<cft::FigureEightMotionBehavior>(data.at("axis").get<Vec3>().value, data.at("radius"), data.at("speed")); });
	factory.registerType("Jitter", [](const json& data) { return std::make_unique<cft::JitterMotionBehavior>(data.at("strength"), data.at("seed")); });
	factory.registerType("Orbit", [](const json& data) { return std::make_unique<cft::OrbitMotionBehavior>(data.at("origin").get<Vec3>().value, data.at("axis").get<Vec3>().value, data.at("radius"), data.at("speed")); });
	factory.registerType("Oscillation", [](const json& data) { return std::make_unique<cft::OscillationMotionBehavior>(data.at("from").get<Vec3>().value, data.at("to").get<Vec3>().value, data.at("speed")); });
	factory.registerType("Path", [](const json& data) { return std::make_unique<cft::PathMotionBehavior>(data.at("path").get<std::vector<lw::Point>>(), data.at("interpolator").get<std::unique_ptr<lw::Interpolator>>(), JsonTools::parseOptionalPointer<lw::Easing>(data.at("easing")), data.at("speed")); });
	factory.registerType("Segment", [](const json& data) { return std::make_unique<cft::SegmentMotionBehavior>(data.at("from").get<Vec3>().value, data.at("to").get<Vec3>().value, data.at("speed")); });
	factory.registerType("Spiral", [](const json& data) { return std::make_unique<cft::SpiralMotionBehavior>(data.at("origin").get<Vec3>().value, data.at("axis").get<Vec3>().value, data.at("startRadius"), data.at("growth"), data.at("speed"), data.at("rise")); });
}