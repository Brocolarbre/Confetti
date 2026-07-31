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
		struct CONFETTI_API AbstractProvider
		{
			virtual ~AbstractProvider() = default;
		};

		template <typename T>
		struct Provider : public AbstractProvider
		{
			std::function<T()> function;

			Provider(std::function<T()> function);
		};

	private:
		std::unordered_map<std::string, std::shared_ptr<AbstractProvider>> m_providers;

	public:
		template <typename T>
		void registerProvider(const std::string& name, std::function<T()> provider);

		template <typename T>
		const std::function<T()>& getProvider(const std::string& name) const;
	};

	template <typename T>
	inline ProviderRegistry::Provider<T>::Provider(std::function<T()> function) :
		function(std::move(function))
	{

	}

	template <typename T>
	inline void ProviderRegistry::registerProvider(const std::string& name, std::function<T()> provider)
	{
		m_providers[name] = std::make_shared<Provider<T>>(std::move(provider));
	}

	template <typename T>
	inline const std::function<T()>& ProviderRegistry::getProvider(const std::string& name) const
	{
		auto it = m_providers.find(name);

		if (it == m_providers.end())
			throw std::runtime_error("Unknown provider : '" + name + "'");

		auto provider = std::static_pointer_cast<Provider<T>>(it->second);

		return provider->function;
	}
}