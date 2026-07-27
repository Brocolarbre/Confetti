#pragma once

#include <nlohmann/json.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/WeightedRandomSetAttributeGenerator.hpp>

class JsonTools
{
private:
	using json = nlohmann::json;

public:
	static glm::quat eulerAnglesToQuaternion(const glm::vec3& eulerAngles);
	static std::vector<glm::quat> eulerAnglesToQuaternion(const std::vector<glm::vec3>& eulerAngles);
	static std::vector<cft::WeightedValue<glm::quat>> eulerAnglesToQuaternion(const std::vector<cft::WeightedValue<glm::vec3>>& eulerAngles);

	template <typename T, typename WrapperType>
	static T wrapperToType(const WrapperType& wrapper);

	template <typename T, typename WrapperType>
	static std::vector<T> wrapperToType(const std::vector<WrapperType>& wrapper);

	template <typename T, typename WrapperType>
	static std::vector<cft::WeightedValue<T>> wrapperToType(const std::vector<cft::WeightedValue<WrapperType>>& wrapper);
};

template<typename T, typename WrapperType>
inline T JsonTools::wrapperToType(const WrapperType& wrapper)
{
	return wrapper.value;
}

template<typename T, typename WrapperType>
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