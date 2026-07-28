#pragma once

#include "JsonTraits.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

#include <Confetti/Emission/AttributeGenerator/Generic/ConstantAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/InterpolatedRandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/LinearAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/RandomAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/RandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/WeightedRandomSetAttributeGenerator.hpp>

class JsonLoaderAttributeGenerator
{
private:
	using json = nlohmann::json;

	template <typename Type, typename WrapperType>
	static std::unique_ptr<cft::AttributeGenerator<Type>> parseSpecializedGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);

	template <>
	static std::unique_ptr<cft::AttributeGenerator<glm::vec3>> parseSpecializedGenerator<glm::vec3, Vec3>(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);

	template <>
	static std::unique_ptr<cft::AttributeGenerator<glm::vec4>> parseSpecializedGenerator<glm::vec4, Color>(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);

	template <typename Type, typename WrapperType>
	static std::unique_ptr<cft::AttributeGenerator<Type>> parseGenericGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);

public:
	template <typename Type, typename WrapperType>
	static std::unique_ptr<cft::AttributeGenerator<Type>> parseAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
};

template <typename Type, typename WrapperType>
inline std::unique_ptr<cft::AttributeGenerator<Type>> JsonLoaderAttributeGenerator::parseSpecializedGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	return nullptr;
}

template <typename Type, typename WrapperType>
inline std::unique_ptr<cft::AttributeGenerator<Type>> JsonLoaderAttributeGenerator::parseGenericGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Constant")
		return std::make_unique<cft::ConstantAttributeGenerator<Type>>(JsonTraits<Type, WrapperType>::read(data["value"]));
	else if (type == "InterpolatedRandomSet")
		return std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<Type>>(JsonTraits<Type, WrapperType>::readVector(data["values"]), randomNumberGenerator);
	else if (type == "Linear")
		return std::make_unique<cft::LinearAttributeGenerator<Type>>(JsonTraits<Type, WrapperType>::read(data["from"]), JsonTraits<Type, WrapperType>::read(data["to"]));
	else if (type == "Random")
		return std::make_unique<cft::RandomAttributeGenerator<Type>>(JsonTraits<Type, WrapperType>::read(data["minimum"]), JsonTraits<Type, WrapperType>::read(data["maximum"]), randomNumberGenerator);
	else if (type == "RandomSet")
		return std::make_unique<cft::RandomSetAttributeGenerator<Type>>(JsonTraits<Type, WrapperType>::readVector(data["values"]), randomNumberGenerator);
	else if (type == "WeightedRandomSet")
		return std::make_unique<cft::WeightedRandomSetAttributeGenerator<Type>>(JsonTraits<Type, WrapperType>::readWeightedVector(data["values"]), randomNumberGenerator);
	else
		throw std::runtime_error("Invalid attribute generator type : '" + type + "'");
}

template <typename Type, typename WrapperType>
inline std::unique_ptr<cft::AttributeGenerator<Type>> JsonLoaderAttributeGenerator::parseAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (std::unique_ptr<cft::AttributeGenerator<Type>> generator = parseSpecializedGenerator<Type, WrapperType>(data, randomNumberGenerator))
		return generator;
	else
		return parseGenericGenerator<Type, WrapperType>(data, randomNumberGenerator);
}
