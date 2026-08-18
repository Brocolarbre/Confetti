#include "Confetti/Serialization/JsonLoader.hpp"
#include "Confetti/Serialization/JsonSerialization.hpp"

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

namespace cft
{
	void JsonLoader::registerTypes(JsonFactory<lw::Easing>& factory, const ProviderRegistry& providerRegistry)
	{
		factory.registerType("EaseCurve", [](const json& data) { return std::make_unique<lw::EaseCurve>(data.at("interpolator").get<std::unique_ptr<lw::Interpolator>>(), data.at("path").get<std::vector<lw::Point>>()); });
		factory.registerType("EaseInBack", [](const json& data) { return std::make_unique<lw::EaseInBack>(); });
		factory.registerType("EaseInBounce", [](const json& data) { return std::make_unique<lw::EaseInBounce>(); });
		factory.registerType("EaseInCircular", [](const json& data) { return std::make_unique<lw::EaseInCircular>(); });
		factory.registerType("EaseInCubic", [](const json& data) { return std::make_unique<lw::EaseInCubic>(); });
		factory.registerType("EaseInElastic", [](const json& data) { return std::make_unique<lw::EaseInElastic>(); });
		factory.registerType("EaseInExponential", [](const json& data) { return std::make_unique<lw::EaseInExponential>(); });
		factory.registerType("EaseInOutBack", [](const json& data) { return std::make_unique<lw::EaseInOutBack>(); });
		factory.registerType("EaseInOutBounce", [](const json& data) { return std::make_unique<lw::EaseInOutBounce>(); });
		factory.registerType("EaseInOutCircular", [](const json& data) { return std::make_unique<lw::EaseInOutCircular>(); });
		factory.registerType("EaseInOutCubic", [](const json& data) { return std::make_unique<lw::EaseInOutCubic>(); });
		factory.registerType("EaseInOutElastic", [](const json& data) { return std::make_unique<lw::EaseInOutElastic>(); });
		factory.registerType("EaseInOutExponential", [](const json& data) { return std::make_unique<lw::EaseInOutExponential>(); });
		factory.registerType("EaseInOutQuadratic", [](const json& data) { return std::make_unique<lw::EaseInOutQuadratic>(); });
		factory.registerType("EaseInOutQuartic", [](const json& data) { return std::make_unique<lw::EaseInOutQuartic>(); });
		factory.registerType("EaseInOutQuintic", [](const json& data) { return std::make_unique<lw::EaseInOutQuintic>(); });
		factory.registerType("EaseInOutSine", [](const json& data) { return std::make_unique<lw::EaseInOutSine>(); });
		factory.registerType("EaseInQuadratic", [](const json& data) { return std::make_unique<lw::EaseInQuadratic>(); });
		factory.registerType("EaseInQuartic", [](const json& data) { return std::make_unique<lw::EaseInQuartic>(); });
		factory.registerType("EaseInQuintic", [](const json& data) { return std::make_unique<lw::EaseInQuintic>(); });
		factory.registerType("EaseInSine", [](const json& data) { return std::make_unique<lw::EaseInSine>(); });
		factory.registerType("EaseLinear", [](const json& data) { return std::make_unique<lw::EaseLinear>(); });
		factory.registerType("EaseOutBack", [](const json& data) { return std::make_unique<lw::EaseOutBack>(); });
		factory.registerType("EaseOutBounce", [](const json& data) { return std::make_unique<lw::EaseOutBounce>(); });
		factory.registerType("EaseOutCircular", [](const json& data) { return std::make_unique<lw::EaseOutCircular>(); });
		factory.registerType("EaseOutCubic", [](const json& data) { return std::make_unique<lw::EaseOutCubic>(); });
		factory.registerType("EaseOutElastic", [](const json& data) { return std::make_unique<lw::EaseOutElastic>(); });
		factory.registerType("EaseOutExponential", [](const json& data) { return std::make_unique<lw::EaseOutExponential>(); });
		factory.registerType("EaseOutQuadratic", [](const json& data) { return std::make_unique<lw::EaseOutQuadratic>(); });
		factory.registerType("EaseOutQuartic", [](const json& data) { return std::make_unique<lw::EaseOutQuartic>(); });
		factory.registerType("EaseOutQuintic", [](const json& data) { return std::make_unique<lw::EaseOutQuintic>(); });
		factory.registerType("EaseOutSine", [](const json& data) { return std::make_unique<lw::EaseOutSine>(); });
		factory.registerType("EaseSmootherstep", [](const json& data) { return std::make_unique<lw::EaseSmootherstep>(); });
		factory.registerType("EaseSmoothstep", [](const json& data) { return std::make_unique<lw::EaseSmoothstep>(); });
	}
}