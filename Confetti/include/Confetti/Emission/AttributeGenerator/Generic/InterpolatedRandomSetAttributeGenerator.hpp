#pragma once

#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	template <typename T>
	class InterpolatedRandomSetAttributeGenerator : public AttributeGenerator<T>
	{
	private:
		std::vector<T> m_values;
		RandomNumberGenerator m_randomNumberGenerator;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) override;

	public:
		InterpolatedRandomSetAttributeGenerator(const std::vector<T>& values, std::uint64_t seed = 0);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;

		std::optional<std::uint64_t> getSeed() const override;
		void setSeed(std::uint64_t seed) override;
	};

	template <typename T>
	inline T InterpolatedRandomSetAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context)
	{
		if (m_values.empty())
			return T{};

		if (m_values.size() == 1)
			return m_values[0];

		unsigned int i = m_randomNumberGenerator.generate(0u, static_cast<unsigned int>(m_values.size() - 2));
		unsigned int j = i + 1;

		float t = m_randomNumberGenerator.generate(0.0f, 1.0f);
		return glm::mix(m_values[i], m_values[j], t);
	}

	template <typename T>
	inline InterpolatedRandomSetAttributeGenerator<T>::InterpolatedRandomSetAttributeGenerator(const std::vector<T>& values, std::uint64_t seed) :
		m_values(values),
		m_randomNumberGenerator(seed)
	{

	}

	template <typename T>
	inline std::unique_ptr<AttributeGenerator<T>> InterpolatedRandomSetAttributeGenerator<T>::clone() const
	{
		return std::make_unique<InterpolatedRandomSetAttributeGenerator<T>>(*this);
	}

	template <typename T>
	inline std::optional<std::uint64_t> InterpolatedRandomSetAttributeGenerator<T>::getSeed() const
	{
		return m_randomNumberGenerator.getSeed();
	}

	template <typename T>
	inline void InterpolatedRandomSetAttributeGenerator<T>::setSeed(std::uint64_t seed)
	{
		m_randomNumberGenerator.setSeed(seed);
	}
}