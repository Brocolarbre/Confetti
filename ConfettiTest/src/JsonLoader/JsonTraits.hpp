#pragma once

#include "JsonSerialization.hpp"

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