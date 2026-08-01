#pragma once

#include <nlohmann/json.hpp>

#include "Confetti/Emission/AttributeGenerator/Generic/WeightedRandomSetAttributeGenerator.hpp"

namespace cft
{
	class JsonTools
	{
	private:
		using json = nlohmann::json;

	public:
		static glm::quat eulerAnglesToQuaternion(const glm::vec3& eulerAngles);
		static std::vector<glm::quat> eulerAnglesToQuaternion(const std::vector<glm::vec3>& eulerAngles);
		static std::vector<cft::WeightedValue<glm::quat>> eulerAnglesToQuaternion(const std::vector<cft::WeightedValue<glm::vec3>>& eulerAngles);

		template <typename T>
		static std::optional<T> parseOptional(const json& data);

		template <typename T>
		static std::unique_ptr<T> parseOptionalPointer(const json& data);

		template <typename T, typename WrapperType>
		static T wrapperToType(const WrapperType& wrapper);

		template <typename T, typename WrapperType>
		static std::vector<T> wrapperToType(const std::vector<WrapperType>& wrapper);

		template <typename T, typename WrapperType>
		static std::vector<cft::WeightedValue<T>> wrapperToType(const std::vector<cft::WeightedValue<WrapperType>>& wrapper);
	};

	template <typename T>
	inline std::optional<T> JsonTools::parseOptional(const json& data)
	{
		if (data.is_null())
			return std::nullopt;

		return std::make_optional<T>(data.get<T>());
	}

	template <typename T>
	inline std::unique_ptr<T> JsonTools::parseOptionalPointer(const json& data)
	{
		if (data.is_null())
			return nullptr;

		return data.get<std::unique_ptr<T>>();
	}

	template <typename T, typename WrapperType>
	inline T JsonTools::wrapperToType(const WrapperType& wrapper)
	{
		return wrapper.value;
	}

	template <typename T, typename WrapperType>
	inline std::vector<T> JsonTools::wrapperToType(const std::vector<WrapperType>& wrapper)
	{
		std::vector<T> type;
		type.reserve(wrapper.size());

		for (const WrapperType& wrapperValue : wrapper)
			type.push_back(wrapperValue.value);

		return type;
	}

	template <typename T, typename WrapperType>
	inline std::vector<cft::WeightedValue<T>> JsonTools::wrapperToType(const std::vector<cft::WeightedValue<WrapperType>>& wrapper)
	{
		std::vector<cft::WeightedValue<T>> type;
		type.reserve(wrapper.size());

		for (const cft::WeightedValue<WrapperType>& wrapperValue : wrapper)
			type.push_back(cft::WeightedValue<T>{ wrapperToType<T>(wrapperValue.value), wrapperValue.weight });

		return type;
	}
}