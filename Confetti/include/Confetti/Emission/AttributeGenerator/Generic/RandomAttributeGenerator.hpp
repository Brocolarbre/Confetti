#pragma once

#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	template <typename T>
	class RandomAttributeGenerator : public Cloneable<RandomAttributeGenerator<T>, AttributeGenerator<T>>
	{
	private:
		T m_minimum;
		T m_maximum;
		RandomNumberGenerator m_randomNumberGenerator;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) override;

	public:
		RandomAttributeGenerator(const T& minimum, const T& maximum, std::uint64_t seed = 0);

		std::optional<std::uint64_t> getSeed() const override;
		void setSeed(std::uint64_t seed) override;
	};

	template <typename T>
	inline T RandomAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context)
	{
		return m_randomNumberGenerator.generate(m_minimum, m_maximum);
	}

	template <typename T>
	inline RandomAttributeGenerator<T>::RandomAttributeGenerator(const T& minimum, const T& maximum, std::uint64_t seed) :
		m_minimum(minimum),
		m_maximum(maximum),
		m_randomNumberGenerator(seed)
	{

	}

	template <typename T>
	inline std::optional<std::uint64_t> RandomAttributeGenerator<T>::getSeed() const
	{
		return m_randomNumberGenerator.getSeed();
	}

	template <typename T>
	inline void RandomAttributeGenerator<T>::setSeed(std::uint64_t seed)
	{
		m_randomNumberGenerator.setSeed(seed);
	}
}