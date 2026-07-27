#include "JsonLoaderAttributeGenerator.hpp"

#include <Confetti/Emission/AttributeGenerator/Specialized/NormalBurstLinearVelocityGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/NormalLinearVelocityGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/RandomNormalOffsetPositionGenerator.hpp>

template <>
cft::UnaryAttributeGenerator<glm::vec3>::UnaryOperation JsonLoaderAttributeGenerator::parseUnaryOperation<glm::vec3>(const json& data)
{
    std::string operation = data["operation"];

    if (operation == "Normalize")
        return [](const glm::vec3& value) { return glm::normalize(value); };

    if (operation == "Clamp")
    {
        glm::vec3 minimum = JsonTraits<glm::vec3, Vec3>::read(data["minimum"]);
        glm::vec3 maximum = JsonTraits<glm::vec3, Vec3>::read(data["maximum"]);

        return [=](const glm::vec3& value) { return glm::clamp(value, minimum, maximum); };
    }
    else
        throw std::runtime_error("Invalid unary operation type : '" + operation + "'");
}

template <>
std::unique_ptr<cft::AttributeGenerator<glm::vec3>> JsonLoaderAttributeGenerator::parseSpecializedGenerator<glm::vec3, Vec3>(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
    std::string type = data["type"];

    if (type == "NormalBurst")
        return std::make_unique<cft::NormalBurstLinearVelocityGenerator>(data["strength"], data["maximumAngle"], randomNumberGenerator);
    else if (type == "Normal")
        return std::make_unique<cft::NormalLinearVelocityGenerator>(data["strength"]);
    else if (type == "RandomNormalOffset")
        return std::make_unique<cft::RandomNormalOffsetPositionGenerator>(data["minimumStrength"], data["maximumStrength"], randomNumberGenerator);
    else
        throw std::runtime_error("Invalid specialized attribute generator type : '" + type + "'");
}