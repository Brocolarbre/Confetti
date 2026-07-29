#pragma once

#include "Confetti/Emission/SpawnShape/SpawnContext.hpp"
#include "Confetti/Tool/Cloneable.hpp"
#include "Confetti/Tool/Seedable.hpp"

#include <memory>
#include <vector>

namespace cft
{
	template <typename T>
	class AttributeGenerator : public Seedable
	{
	private:
		virtual T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) = 0;

	public:
		virtual ~AttributeGenerator() = default;

		virtual std::unique_ptr<AttributeGenerator<T>> clone() const = 0;

		virtual std::vector<T> generate(unsigned int count, const std::vector<SpawnContext>& context);
	};

	template <typename T>
	inline std::vector<T> AttributeGenerator<T>::generate(unsigned int count, const std::vector<SpawnContext>& context)
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