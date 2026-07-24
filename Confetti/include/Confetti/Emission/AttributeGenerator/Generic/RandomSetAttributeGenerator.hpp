#pragma once

#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	template <typename T>
	class RandomSetAttributeGenerator : public AttributeGenerator<T>
	{
	private:
		std::vector<T> m_values;
		RandomNumberGenerator& m_randomNumberGenerator;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		RandomSetAttributeGenerator(const std::vector<T>& values, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T RandomSetAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
	{
		if (m_values.empty())
			return T{};

		return m_values[m_randomNumberGenerator.generateInteger(0u, static_cast<unsigned int>(m_values.size()) - 1)];
	}

	template<typename T>
	inline RandomSetAttributeGenerator<T>::RandomSetAttributeGenerator(const std::vector<T>& values, RandomNumberGenerator& randomNumberGenerator) :
		m_values(values),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	template<typename T>
	inline std::unique_ptr<AttributeGenerator<T>> RandomSetAttributeGenerator<T>::clone() const
	{
		return std::make_unique<RandomSetAttributeGenerator<T>>(*this);
	}
}