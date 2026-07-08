#pragma once

#include "Confetti/ParticleSpawner/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	template <typename T>
	class WeightedRandomSetAttributeGenerator : public AttributeGenerator<T>
	{
	public:
		struct WeightedValue
		{
			T value;
			unsigned int weight;
		};

	private:
		std::vector<WeightedValue> m_values;
		unsigned int m_totalWeight;
		RandomNumberGenerator& m_randomNumberGenerator;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		WeightedRandomSetAttributeGenerator(const std::vector<WeightedValue>& values, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T WeightedRandomSetAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
	{
		if (m_values.empty())
			return T(0.0f);

		unsigned int randomIndex = m_randomNumberGenerator.generateInteger(0u, m_totalWeight - 1);
		unsigned int accumulator = 0;

		for (const WeightedValue& value : m_values)
		{
			accumulator += value.weight;
			if (accumulator > randomIndex)
				return value.value;
		}

		return m_values.back().value;
	}

	template<typename T>
	inline WeightedRandomSetAttributeGenerator<T>::WeightedRandomSetAttributeGenerator(const std::vector<WeightedValue>& values, RandomNumberGenerator& randomNumberGenerator) :
		m_values(values),
		m_totalWeight(0),
		m_randomNumberGenerator(randomNumberGenerator)
	{
		for (const WeightedValue& value : m_values)
			m_totalWeight += value.weight;
	}

	template<typename T>
	inline std::unique_ptr<AttributeGenerator<T>> WeightedRandomSetAttributeGenerator<T>::clone() const
	{
		return std::make_unique<WeightedRandomSetAttributeGenerator<T>>(*this);
	}
}