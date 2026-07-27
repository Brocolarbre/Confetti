#pragma once

#include "JsonSerialization.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

#include <Confetti/Emission/AttributeGenerator/BinaryAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/UnaryAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/ConstantAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/InterpolatedRandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/LinearAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/RandomAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/RandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/WeightedRandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/NormalBurstLinearVelocityGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/NormalLinearVelocityGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/RandomNormalOffsetPositionGenerator.hpp>

template <typename Type, typename WrapperType>
struct JsonTraits;

template <>
struct JsonTraits<cft::Color, Color>
{
	static cft::Color read(const nlohmann::json& data)
	{
		return data.get<Color>().value;
	}

	static std::vector<cft::Color> readVector(const nlohmann::json& data)
	{
		return JsonTools::wrapperToType<cft::Color>(data.get<std::vector<Color>>());
	}

	static std::vector<cft::WeightedValue<cft::Color>> readWeightedVector(const nlohmann::json& data)
	{
		return JsonTools::wrapperToType<cft::Color>(data.get<std::vector<cft::WeightedValue<Color>>>());
	}
};

template <>
struct JsonTraits<cft::Position, Vec3>
{
	static cft::Position read(const nlohmann::json& data)
	{
		return data.get<Vec3>().value;
	}

	static std::vector<cft::Position> readVector(const nlohmann::json& data)
	{
		return JsonTools::wrapperToType<cft::Position>(data.get<std::vector<Vec3>>());
	}

	static std::vector<cft::WeightedValue<cft::Position>> readWeightedVector(const nlohmann::json& data)
	{
		return JsonTools::wrapperToType<cft::Position>(data.get<std::vector<cft::WeightedValue<Vec3>>>());
	}
};

template <>
struct JsonTraits<cft::Rotation, Vec3>
{
	static cft::Rotation read(const nlohmann::json& data)
	{
		return JsonTools::eulerAnglesToQuaternion(data.get<Vec3>().value);
	}

	static std::vector<cft::Rotation> readVector(const nlohmann::json& data)
	{
		return JsonTools::eulerAnglesToQuaternion(JsonTools::wrapperToType<glm::vec3>(data.get<std::vector<Vec3>>()));
	}

	static std::vector<cft::WeightedValue<cft::Rotation>> readWeightedVector(const nlohmann::json& data)
	{
		return JsonTools::eulerAnglesToQuaternion(JsonTools::wrapperToType<glm::vec3>(data.get<std::vector<cft::WeightedValue<Vec3>>>()));
	}
};

template <>
struct JsonTraits<cft::Phase, float>
{
	static cft::Phase read(const nlohmann::json& data)
	{
		return data.get<float>();
	}

	static std::vector<cft::Phase> readVector(const nlohmann::json& data)
	{
		return data.get<std::vector<float>>();
	}

	static std::vector<cft::WeightedValue<cft::Phase>> readWeightedVector(const nlohmann::json& data)
	{
		return data.get<std::vector<cft::WeightedValue<float>>>();
	}
};

class JsonLoaderAttributeGenerator
{
public:
	template <typename Type, typename WrapperType>
	static std::unique_ptr<cft::AttributeGenerator<Type>> parseAttributeGenerator(const nlohmann::json& data, cft::RandomNumberGenerator& randomNumberGenerator);
};

template <typename Type, typename WrapperType>
inline std::unique_ptr<cft::AttributeGenerator<Type>> JsonLoaderAttributeGenerator::parseAttributeGenerator(const nlohmann::json& data, cft::RandomNumberGenerator& randomNumberGenerator)
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
