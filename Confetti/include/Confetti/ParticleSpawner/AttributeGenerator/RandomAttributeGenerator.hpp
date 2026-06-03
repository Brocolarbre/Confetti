#pragma once

#include "AttributeGenerator.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	template <typename T>
	class RandomAttributeGenerator : public AttributeGenerator<T>
	{
	private:
		T m_minimum;
		T m_maximum;
		RandomNumberGenerator& m_randomNumberGenerator;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		RandomAttributeGenerator(const T& minimum, const T& maximum, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T RandomAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
	{
		return m_randomNumberGenerator.generate(m_minimum, m_maximum);
	}

	template<typename T>
	inline RandomAttributeGenerator<T>::RandomAttributeGenerator(const T& minimum, const T& maximum, RandomNumberGenerator& randomNumberGenerator) :
		m_minimum(minimum),
		m_maximum(maximum),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	template<typename T>
	inline std::unique_ptr<AttributeGenerator<T>> RandomAttributeGenerator<T>::clone() const
	{
		return std::make_unique<RandomAttributeGenerator<T>>(*this);
	}
}