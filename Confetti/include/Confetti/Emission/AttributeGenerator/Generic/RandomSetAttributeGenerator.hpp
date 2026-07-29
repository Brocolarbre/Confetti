#pragma once

#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	template <typename T>
	class RandomSetAttributeGenerator : public Cloneable<RandomSetAttributeGenerator<T>, AttributeGenerator<T>>
	{
	private:
		std::vector<T> m_values;
		RandomNumberGenerator m_randomNumberGenerator;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) override;

	public:
		RandomSetAttributeGenerator(const std::vector<T>& values, std::uint64_t seed = 0);

		std::optional<std::uint64_t> getSeed() const override;
		void setSeed(std::uint64_t seed) override;
	};

	template <typename T>
	inline T RandomSetAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context)
	{
		if (m_values.empty())
			return T{};

		return m_values[m_randomNumberGenerator.generate(0u, static_cast<unsigned int>(m_values.size()) - 1)];
	}

	template <typename T>
	inline RandomSetAttributeGenerator<T>::RandomSetAttributeGenerator(const std::vector<T>& values, std::uint64_t seed) :
		m_values(values),
		m_randomNumberGenerator(seed)
	{

	}

	template <typename T>
	inline std::optional<std::uint64_t> RandomSetAttributeGenerator<T>::getSeed() const
	{
		return m_randomNumberGenerator.getSeed();
	}

	template <typename T>
	inline void RandomSetAttributeGenerator<T>::setSeed(std::uint64_t seed)
	{
		m_randomNumberGenerator.setSeed(seed);
	}
}