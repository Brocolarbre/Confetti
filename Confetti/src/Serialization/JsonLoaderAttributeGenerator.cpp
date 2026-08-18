#include "Confetti/Serialization/JsonLoaderAttributeGenerator.hpp"

#include "Confetti/Emission/AttributeGenerator/Specialized/BrightnessColorGenerator.hpp"
#include "Confetti/Emission/AttributeGenerator/Specialized/NormalBurstLinearVelocityGenerator.hpp"
#include "Confetti/Emission/AttributeGenerator/Specialized/NormalLinearVelocityGenerator.hpp"
#include "Confetti/Emission/AttributeGenerator/Specialized/RandomNormalOffsetPositionGenerator.hpp"
#include "Confetti/Emission/AttributeGenerator/Specialized/ValueStrengthGenerator.hpp"

namespace cft
{
    template <>
    std::unique_ptr<AttributeGenerator<glm::vec3>> JsonLoaderAttributeGenerator::parseSpecializedGenerator<glm::vec3, JsonTypes::Vec3>(const json& data)
    {
        std::string type = data.at("type");

        if (type == "NormalBurstLinearVelocity")
            return std::make_unique<NormalBurstLinearVelocityGenerator>(data.at("strength"), data.at("maximumAngle"), data.at("seed"));
        else if (type == "NormalLinearVelocity")
            return std::make_unique<NormalLinearVelocityGenerator>(data.at("strength"));
        else if (type == "RandomNormalOffsetPosition")
            return std::make_unique<RandomNormalOffsetPositionGenerator>(data.at("minimumStrength"), data.at("maximumStrength"), data.at("seed"));
        else if (type == "ValueStrength")
            return std::make_unique<ValueStrengthGenerator>(parseAttributeGenerator<glm::vec3, JsonTypes::Vec3>(data.at("valueGenerator")), parseAttributeGenerator<float, float>(data.at("strengthGenerator")));
        else
            return nullptr;
    }

    template <>
    std::unique_ptr<AttributeGenerator<glm::vec4>> JsonLoaderAttributeGenerator::parseSpecializedGenerator<glm::vec4, JsonTypes::Color>(const json& data)
    {
        std::string type = data.at("type");

        if (type == "BrightnessColor")
            return std::make_unique<BrightnessColorGenerator>(parseAttributeGenerator<Color, JsonTypes::Color>(data.at("colorGenerator")), parseAttributeGenerator<float, float>(data.at("brightnessGenerator")));
        else
            return nullptr;
    }
}