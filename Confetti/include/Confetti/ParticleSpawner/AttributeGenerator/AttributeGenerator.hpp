#pragma once

#include "Confetti/ParticleSpawner/SpawnShape/SpawnContext.hpp"

#include <memory>
#include <vector>

namespace cft
{
	template <typename T>
	class AttributeGenerator
	{
	protected:
		virtual T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const = 0;

	public:
		virtual ~AttributeGenerator() = default;

		virtual std::vector<T> generate(unsigned int count, const std::vector<SpawnContext>& context) const;
		virtual std::unique_ptr<AttributeGenerator<T>> clone() const = 0;
	};

	template<typename T>
	inline std::vector<T> AttributeGenerator<T>::generate(unsigned int count, const std::vector<SpawnContext>& context) const
	{
		if (context.size() != count)
			return {};

		std::vector<T> values;
		values.reserve(count);

		for (unsigned int i = 0; i < count; ++i)
			values.push_back(generateValue(count, i, context[i]));

		return values;
	}
}