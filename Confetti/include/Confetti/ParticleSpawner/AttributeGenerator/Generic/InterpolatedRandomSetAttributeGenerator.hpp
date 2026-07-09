#pragma once

#include "Confetti/ParticleSpawner/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	template <typename T>
	class InterpolatedRandomSetAttributeGenerator : public AttributeGenerator<T>
	{
	private:
		std::vector<T> m_values;
		RandomNumberGenerator& m_randomNumberGenerator;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		InterpolatedRandomSetAttributeGenerator(const std::vector<T>& values, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T InterpolatedRandomSetAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
	{
		if (m_values.empty())
			return T(0.0f);

		if (m_values.size() == 1)
			return m_values[0];

		unsigned int i = m_randomNumberGenerator.generateInteger(0u, static_cast<unsigned int>(m_values.size() - 2));
		unsigned int j = i + 1;

		float t = m_randomNumberGenerator.generate(0.0f, 1.0f);
		return glm::mix(m_values[i], m_values[j], t);
	}

	template<typename T>
	inline InterpolatedRandomSetAttributeGenerator<T>::InterpolatedRandomSetAttributeGenerator(const std::vector<T>& values, RandomNumberGenerator& randomNumberGenerator) :
		m_values(values),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	template<typename T>
	inline std::unique_ptr<AttributeGenerator<T>> InterpolatedRandomSetAttributeGenerator<T>::clone() const
	{
		return std::make_unique<InterpolatedRandomSetAttributeGenerator<T>>(*this);
	}
}