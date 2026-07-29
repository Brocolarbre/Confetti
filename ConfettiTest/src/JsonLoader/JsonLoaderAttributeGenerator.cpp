#include "JsonLoaderAttributeGenerator.hpp"

#include <Confetti/Emission/AttributeGenerator/Specialized/BrightnessColorGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/NormalBurstLinearVelocityGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/NormalLinearVelocityGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/RandomNormalOffsetPositionGenerator.hpp>

template <>
std::unique_ptr<cft::AttributeGenerator<glm::vec3>> JsonLoaderAttributeGenerator::parseSpecializedGenerator<glm::vec3, Vec3>(const json& data)
{
    std::string type = data["type"];

    if (type == "NormalBurst")
        return std::make_unique<cft::NormalBurstLinearVelocityGenerator>(data["strength"], data["maximumAngle"], data["seed"]);
    else if (type == "Normal")
        return std::make_unique<cft::NormalLinearVelocityGenerator>(data["strength"]);
    else if (type == "RandomNormalOffset")
        return std::make_unique<cft::RandomNormalOffsetPositionGenerator>(data["minimumStrength"], data["maximumStrength"], data["seed"]);
    else
        return nullptr;
}

template <>
std::unique_ptr<cft::AttributeGenerator<glm::vec4>> JsonLoaderAttributeGenerator::parseSpecializedGenerator<glm::vec4, Color>(const json& data)
{
    std::string type = data["type"];

    if (type == "BrightnessColor")
        return std::make_unique<cft::BrightnessColorGenerator>(parseAttributeGenerator<cft::Color, Color>(data["color"]), parseAttributeGenerator<float, float>(data["brightness"]));
    else
        return nullptr;
}