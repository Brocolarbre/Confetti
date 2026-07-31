#pragma once

#include "Confetti/Export.hpp"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace cft
{
	class ProviderRegistry
	{
	private:
		std::unordered_map<std::string, std::any> m_providers;

	public:
		template <typename T>
		void registerProvider(const std::string& name, std::function<T()> provider);

		template <typename T>
		const std::function<T()>& getProvider(const std::string& name) const;
	};

	template <typename T>
	inline void ProviderRegistry::registerProvider(const std::string& name, std::function<T()> provider)
	{
		m_providers[name] = std::move(provider);
	}

	template <typename T>
	inline const std::function<T()>& ProviderRegistry::getProvider(const std::string& name) const
	{
		auto it = m_providers.find(name);

		if (it == m_providers.end())
			throw std::runtime_error("Unknown provider : '" + name + "'");

		return std::any_cast<const std::function<T()>&>(it->second);
	}
}