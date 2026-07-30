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

namespace cft
{
	class JsonLoaderAttributeGenerator
	{
	private:
		using json = nlohmann::json;

		template <typename Type, typename WrapperType>
		static std::unique_ptr<cft::AttributeGenerator<Type>> parseSpecializedGenerator(const json& data);

		template <typename Type, typename WrapperType>
		static std::unique_ptr<cft::AttributeGenerator<Type>> parseGenericGenerator(const json& data);

	public:
		template <typename Type, typename WrapperType>
		static std::unique_ptr<cft::AttributeGenerator<Type>> parseAttributeGenerator(const json& data);
	};

	template <>
	static std::unique_ptr<cft::AttributeGenerator<glm::vec3>> JsonLoaderAttributeGenerator::parseSpecializedGenerator<glm::vec3, JsonTypes::Vec3>(const json& data);

	template <>
	static std::unique_ptr<cft::AttributeGenerator<glm::vec4>> JsonLoaderAttributeGenerator::parseSpecializedGenerator<glm::vec4, JsonTypes::Color>(const json& data);

	template <typename Type, typename WrapperType>
	inline std::unique_ptr<cft::AttributeGenerator<Type>> JsonLoaderAttributeGenerator::parseSpecializedGenerator(const json& data)
	{
		return nullptr;
	}

	template <typename Type, typename WrapperType>
	inline std::unique_ptr<cft::AttributeGenerator<Type>> JsonLoaderAttributeGenerator::parseGenericGenerator(const json& data)
	{
		std::string type = data.at("type");

		if (type == "Constant")
			return std::make_unique<cft::ConstantAttributeGenerator<Type>>(JsonTraits<Type, WrapperType>::read(data.at("value")));
		else if (type == "InterpolatedRandomSet")
			return std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<Type>>(JsonTraits<Type, WrapperType>::readVector(data.at("values")), data.at("seed"));
		else if (type == "Linear")
			return std::make_unique<cft::LinearAttributeGenerator<Type>>(JsonTraits<Type, WrapperType>::read(data.at("from")), JsonTraits<Type, WrapperType>::read(data.at("to")));
		else if (type == "Random")
			return std::make_unique<cft::RandomAttributeGenerator<Type>>(JsonTraits<Type, WrapperType>::read(data.at("minimum")), JsonTraits<Type, WrapperType>::read(data.at("maximum")), data.at("seed"));
		else if (type == "RandomSet")
			return std::make_unique<cft::RandomSetAttributeGenerator<Type>>(JsonTraits<Type, WrapperType>::readVector(data.at("values")), data.at("seed"));
		else if (type == "WeightedRandomSet")
			return std::make_unique<cft::WeightedRandomSetAttributeGenerator<Type>>(JsonTraits<Type, WrapperType>::readWeightedVector(data.at("values")), data.at("seed"));
		else
			throw std::runtime_error("Invalid attribute generator type : '" + type + "'");
	}

	template <typename Type, typename WrapperType>
	inline std::unique_ptr<cft::AttributeGenerator<Type>> JsonLoaderAttributeGenerator::parseAttributeGenerator(const json& data)
	{
		std::string type = data.at("type");

		if (std::unique_ptr<cft::AttributeGenerator<Type>> generator = parseSpecializedGenerator<Type, WrapperType>(data))
			return generator;
		else
			return parseGenericGenerator<Type, WrapperType>(data);
	}
}