#pragma once

#include "JsonSerialization.hpp"

namespace cft
{
	template <typename Type, typename WrapperType>
	struct JsonTraits
	{
	public:
		static Type read(const nlohmann::json& data);
		static std::vector<Type> readVector(const nlohmann::json& data);
		static std::vector<cft::WeightedValue<Type>> readWeightedVector(const nlohmann::json& data);
	};

	template <typename Type, typename WrapperType>
	inline Type JsonTraits<Type, WrapperType>::read(const nlohmann::json& data)
	{
		return data.get<Type>();
	}

	template <typename Type, typename WrapperType>
	inline std::vector<Type> JsonTraits<Type, WrapperType>::readVector(const nlohmann::json& data)
	{
		return std::vector<Type>();
	}

	template <typename Type, typename WrapperType>
	inline std::vector<cft::WeightedValue<Type>> JsonTraits<Type, WrapperType>::readWeightedVector(const nlohmann::json& data)
	{
		return std::vector<cft::WeightedValue<Type>>();
	}

	template <>
	struct JsonTraits<cft::Color, JsonTypes::Color>
	{
		static cft::Color read(const nlohmann::json& data)
		{
			return data.get<JsonTypes::Color>().value;
		}

		static std::vector<cft::Color> readVector(const nlohmann::json& data)
		{
			return JsonTools::wrapperToType<cft::Color>(data.get<std::vector<JsonTypes::Color>>());
		}

		static std::vector<cft::WeightedValue<cft::Color>> readWeightedVector(const nlohmann::json& data)
		{
			return JsonTools::wrapperToType<cft::Color>(data.get<std::vector<cft::WeightedValue<JsonTypes::Color>>>());
		}
	};

	template <>
	struct JsonTraits<cft::Position, JsonTypes::Vec3>
	{
		static cft::Position read(const nlohmann::json& data)
		{
			return data.get<JsonTypes::Vec3>().value;
		}

		static std::vector<cft::Position> readVector(const nlohmann::json& data)
		{
			return JsonTools::wrapperToType<cft::Position>(data.get<std::vector<JsonTypes::Vec3>>());
		}

		static std::vector<cft::WeightedValue<cft::Position>> readWeightedVector(const nlohmann::json& data)
		{
			return JsonTools::wrapperToType<cft::Position>(data.get<std::vector<cft::WeightedValue<JsonTypes::Vec3>>>());
		}
	};

	template <>
	struct JsonTraits<cft::Rotation, JsonTypes::Vec3>
	{
		static cft::Rotation read(const nlohmann::json& data)
		{
			return JsonTools::eulerAnglesToQuaternion(data.get<JsonTypes::Vec3>().value);
		}

		static std::vector<cft::Rotation> readVector(const nlohmann::json& data)
		{
			return JsonTools::eulerAnglesToQuaternion(JsonTools::wrapperToType<glm::vec3>(data.get<std::vector<JsonTypes::Vec3>>()));
		}

		static std::vector<cft::WeightedValue<cft::Rotation>> readWeightedVector(const nlohmann::json& data)
		{
			return JsonTools::eulerAnglesToQuaternion(JsonTools::wrapperToType<glm::vec3>(data.get<std::vector<cft::WeightedValue<JsonTypes::Vec3>>>()));
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
}