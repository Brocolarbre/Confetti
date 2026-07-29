#pragma once

#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	template <typename T>
	struct WeightedValue
	{
		T value;
		unsigned int weight;
	};

	template <typename T>
	class WeightedRandomSetAttributeGenerator : public Cloneable<WeightedRandomSetAttributeGenerator<T>, AttributeGenerator<T>>
	{
	public:
		using WeightedValue = WeightedValue<T>;

	private:
		std::vector<WeightedValue> m_values;
		unsigned int m_totalWeight;
		RandomNumberGenerator m_randomNumberGenerator;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) override;

	public:
		WeightedRandomSetAttributeGenerator(const std::vector<WeightedValue>& values, std::uint64_t seed = 0);

		std::optional<std::uint64_t> getSeed() const override;
		void setSeed(std::uint64_t seed) override;
	};

	template <typename T>
	inline T WeightedRandomSetAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context)
	{
		if (m_values.empty())
			return T{};

		unsigned int randomIndex = m_randomNumberGenerator.generate(0u, m_totalWeight - 1);
		unsigned int accumulator = 0;

		for (const WeightedValue& value : m_values)
		{
			accumulator += value.weight;
			if (accumulator > randomIndex)
				return value.value;
		}

		return m_values.back().value;
	}

	template <typename T>
	inline WeightedRandomSetAttributeGenerator<T>::WeightedRandomSetAttributeGenerator(const std::vector<WeightedValue>& values, std::uint64_t seed) :
		m_values(values),
		m_totalWeight(0),
		m_randomNumberGenerator(seed)
	{
		for (const WeightedValue& value : m_values)
			m_totalWeight += value.weight;
	}

	template <typename T>
	inline std::optional<std::uint64_t> WeightedRandomSetAttributeGenerator<T>::getSeed() const
	{
		return m_randomNumberGenerator.getSeed();
	}

	template <typename T>
	inline void WeightedRandomSetAttributeGenerator<T>::setSeed(std::uint64_t seed)
	{
		m_randomNumberGenerator.setSeed(seed);
	}
}