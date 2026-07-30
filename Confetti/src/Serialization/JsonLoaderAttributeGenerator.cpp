#include "Confetti/Serialization/JsonLoaderAttributeGenerator.hpp"

#include <Confetti/Emission/AttributeGenerator/Specialized/BrightnessColorGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/NormalBurstLinearVelocityGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/NormalLinearVelocityGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/RandomNormalOffsetPositionGenerator.hpp>

namespace cft
{
    template <>
    std::unique_ptr<cft::AttributeGenerator<glm::vec3>> JsonLoaderAttributeGenerator::parseSpecializedGenerator<glm::vec3, JsonTypes::Vec3>(const json& data)
    {
        std::string type = data.at("type");

        if (type == "NormalBurst")
            return std::make_unique<cft::NormalBurstLinearVelocityGenerator>(data.at("strength"), data.at("maximumAngle"), data.at("seed"));
        else if (type == "Normal")
            return std::make_unique<cft::NormalLinearVelocityGenerator>(data.at("strength"));
        else if (type == "RandomNormalOffset")
            return std::make_unique<cft::RandomNormalOffsetPositionGenerator>(data.at("minimumStrength"), data.at("maximumStrength"), data.at("seed"));
        else
            return nullptr;
    }

    template <>
    std::unique_ptr<cft::AttributeGenerator<glm::vec4>> JsonLoaderAttributeGenerator::parseSpecializedGenerator<glm::vec4, JsonTypes::Color>(const json& data)
    {
        std::string type = data.at("type");

        if (type == "BrightnessColor")
            return std::make_unique<cft::BrightnessColorGenerator>(parseAttributeGenerator<cft::Color, JsonTypes::Color>(data.at("color")), parseAttributeGenerator<float, float>(data.at("brightness")));
        else
            return nullptr;
    }
}