#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonSerialization.hpp"

#include <LineWeaver/Interpolation/BezierInterpolator.hpp>
#include <LineWeaver/Interpolation/BSplineInterpolator.hpp>
#include <LineWeaver/Interpolation/CatmullRomInterpolator.hpp>
#include <LineWeaver/Interpolation/HermiteInterpolator.hpp>
#include <LineWeaver/Interpolation/LinearInterpolator.hpp>

namespace cft
{
	void JsonLoader::registerTypes(JsonFactory<lw::Interpolator>& factory)
	{
		factory.registerType("Bezier", [](const json& data) { return std::make_unique<lw::BezierInterpolator>(data.at("pointsPerSegment")); });
		factory.registerType("BSpline", [](const json& data) { return std::make_unique<lw::BSplineInterpolator>(data.at("interpolator").get<std::unique_ptr<lw::Interpolator>>()); });
		factory.registerType("CatmullRom", [](const json& data) { return std::make_unique<lw::CatmullRomInterpolator>(); });
		factory.registerType("Hermite", [](const json& data) { return std::make_unique<lw::HermiteInterpolator>(); });
		factory.registerType("Linear", [](const json& data) { return std::make_unique<lw::LinearInterpolator>(); });
	}
}