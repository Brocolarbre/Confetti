#pragma once

#include <nlohmann/json.hpp>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

template <typename Base>
class JsonFactory
{
private:
	using json = nlohmann::json;

public:
	using Factory = std::function<std::unique_ptr<Base>(const json& data)>;

private:
	std::unordered_map<std::string, Factory> m_factories;

public:
	void registerType(const std::string& type, Factory factory);
	std::unique_ptr<Base> instantiate(const json& data) const;
};

template <typename Base>
inline void JsonFactory<Base>::registerType(const std::string& type, Factory factory)
{
	m_factories.try_emplace(type, std::move(factory));
}

template <typename Base>
inline std::unique_ptr<Base> JsonFactory<Base>::instantiate(const json& data) const
{
	std::string type = data.at("type");

	auto it = m_factories.find(type);

	if (it == m_factories.end())
		throw std::runtime_error("Unknown type : '" + type + "'");

	return it->second(data);
}