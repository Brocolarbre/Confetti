#include "JsonLoader.hpp"
#include "JsonSerialization.hpp"

#include <LineWeaver/Easing/EaseCurve.hpp>
#include <LineWeaver/Easing/EaseInBack.hpp>
#include <LineWeaver/Easing/EaseInBounce.hpp>
#include <LineWeaver/Easing/EaseInCircular.hpp>
#include <LineWeaver/Easing/EaseInCubic.hpp>
#include <LineWeaver/Easing/EaseInElastic.hpp>
#include <LineWeaver/Easing/EaseInExponential.hpp>
#include <LineWeaver/Easing/EaseInOutBack.hpp>
#include <LineWeaver/Easing/EaseInOutBounce.hpp>
#include <LineWeaver/Easing/EaseInOutCircular.hpp>
#include <LineWeaver/Easing/EaseInOutCubic.hpp>
#include <LineWeaver/Easing/EaseInOutElastic.hpp>
#include <LineWeaver/Easing/EaseInOutExponential.hpp>
#include <LineWeaver/Easing/EaseInOutQuadratic.hpp>
#include <LineWeaver/Easing/EaseInOutQuartic.hpp>
#include <LineWeaver/Easing/EaseInOutQuintic.hpp>
#include <LineWeaver/Easing/EaseInOutSine.hpp>
#include <LineWeaver/Easing/EaseInQuadratic.hpp>
#include <LineWeaver/Easing/EaseInQuartic.hpp>
#include <LineWeaver/Easing/EaseInQuintic.hpp>
#include <LineWeaver/Easing/EaseInSine.hpp>
#include <LineWeaver/Easing/EaseLinear.hpp>
#include <LineWeaver/Easing/EaseOutBack.hpp>
#include <LineWeaver/Easing/EaseOutBounce.hpp>
#include <LineWeaver/Easing/EaseOutCircular.hpp>
#include <LineWeaver/Easing/EaseOutCubic.hpp>
#include <LineWeaver/Easing/EaseOutElastic.hpp>
#include <LineWeaver/Easing/EaseOutExponential.hpp>
#include <LineWeaver/Easing/EaseOutQuadratic.hpp>
#include <LineWeaver/Easing/EaseOutQuartic.hpp>
#include <LineWeaver/Easing/EaseOutQuintic.hpp>
#include <LineWeaver/Easing/EaseOutSine.hpp>
#include <LineWeaver/Easing/EaseSmootherstep.hpp>
#include <LineWeaver/Easing/EaseSmoothstep.hpp>

void JsonLoader::registerTypes(JsonFactory<lw::Easing>& factory)
{
	factory.registerType("Curve", [](const json& data) { return std::make_unique<lw::EaseCurve>(data.at("interpolator").get<std::unique_ptr<lw::Interpolator>>(), data.at("path").get<std::vector<lw::Point>>()); });
	factory.registerType("InBack", [](const json& data) { return std::make_unique<lw::EaseInBack>(); });
	factory.registerType("InBounce", [](const json& data) { return std::make_unique<lw::EaseInBounce>(); });
	factory.registerType("InCircular", [](const json& data) { return std::make_unique<lw::EaseInCircular>(); });
	factory.registerType("InCubic", [](const json& data) { return std::make_unique<lw::EaseInCubic>(); });
	factory.registerType("InElastic", [](const json& data) { return std::make_unique<lw::EaseInElastic>(); });
	factory.registerType("InExponential", [](const json& data) { return std::make_unique<lw::EaseInExponential>(); });
	factory.registerType("InOutBack", [](const json& data) { return std::make_unique<lw::EaseInOutBack>(); });
	factory.registerType("InOutBounce", [](const json& data) { return std::make_unique<lw::EaseInOutBounce>(); });
	factory.registerType("InOutCircular", [](const json& data) { return std::make_unique<lw::EaseInOutCircular>(); });
	factory.registerType("InOutCubic", [](const json& data) { return std::make_unique<lw::EaseInOutCubic>(); });
	factory.registerType("InOutElastic", [](const json& data) { return std::make_unique<lw::EaseInOutElastic>(); });
	factory.registerType("InOutExponential", [](const json& data) { return std::make_unique<lw::EaseInOutExponential>(); });
	factory.registerType("InOutQuadratic", [](const json& data) { return std::make_unique<lw::EaseInOutQuadratic>(); });
	factory.registerType("InOutQuartic", [](const json& data) { return std::make_unique<lw::EaseInOutQuartic>(); });
	factory.registerType("InOutQuintic", [](const json& data) { return std::make_unique<lw::EaseInOutQuintic>(); });
	factory.registerType("InOutSine", [](const json& data) { return std::make_unique<lw::EaseInOutSine>(); });
	factory.registerType("InQuadratic", [](const json& data) { return std::make_unique<lw::EaseInQuadratic>(); });
	factory.registerType("InQuartic", [](const json& data) { return std::make_unique<lw::EaseInQuartic>(); });
	factory.registerType("InQuintic", [](const json& data) { return std::make_unique<lw::EaseInQuintic>(); });
	factory.registerType("InSine", [](const json& data) { return std::make_unique<lw::EaseInSine>(); });
	factory.registerType("Linear", [](const json& data) { return std::make_unique<lw::EaseLinear>(); });
	factory.registerType("OutBack", [](const json& data) { return std::make_unique<lw::EaseOutBack>(); });
	factory.registerType("OutBounce", [](const json& data) { return std::make_unique<lw::EaseOutBounce>(); });
	factory.registerType("OutCircular", [](const json& data) { return std::make_unique<lw::EaseOutCircular>(); });
	factory.registerType("OutCubic", [](const json& data) { return std::make_unique<lw::EaseOutCubic>(); });
	factory.registerType("OutElastic", [](const json& data) { return std::make_unique<lw::EaseOutElastic>(); });
	factory.registerType("OutExponential", [](const json& data) { return std::make_unique<lw::EaseOutExponential>(); });
	factory.registerType("OutQuadratic", [](const json& data) { return std::make_unique<lw::EaseOutQuadratic>(); });
	factory.registerType("OutQuartic", [](const json& data) { return std::make_unique<lw::EaseOutQuartic>(); });
	factory.registerType("OutQuintic", [](const json& data) { return std::make_unique<lw::EaseOutQuintic>(); });
	factory.registerType("OutSine", [](const json& data) { return std::make_unique<lw::EaseOutSine>(); });
	factory.registerType("Smootherstep", [](const json& data) { return std::make_unique<lw::EaseSmootherstep>(); });
	factory.registerType("Smoothstep", [](const json& data) { return std::make_unique<lw::EaseSmoothstep>(); });
}