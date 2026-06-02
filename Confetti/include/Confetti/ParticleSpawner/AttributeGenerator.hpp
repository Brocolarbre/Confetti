#pragma once

#include "Confetti/Tools/RandomNumberGenerator.hpp"

#include <vector>

namespace cft
{
	template <typename T>
	class AttributeGenerator
	{
	protected:
		virtual T generateValue(unsigned int count, unsigned int index) const = 0;

	public:
		virtual ~AttributeGenerator() = default;

		virtual std::vector<T> generate(unsigned int count) const;
		virtual std::unique_ptr<AttributeGenerator<T>> clone() const = 0;
	};

	template<typename T>
	inline std::vector<T> AttributeGenerator<T>::generate(unsigned int count) const
	{
		std::vector<T> values;
		values.reserve(count);

		for (unsigned int i = 0; i < count; ++i)
			values.push_back(generateValue(count, i));

		return values;
	}

	template <typename T>
	class ConstantAttributeGenerator : public AttributeGenerator<T>
	{
	private:
		T m_value;

		T generateValue(unsigned int count, unsigned int index) const override;

	public:
		ConstantAttributeGenerator(const T& value);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T ConstantAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index) const
	{
		return m_value;
	}

	template<typename T>
	inline ConstantAttributeGenerator<T>::ConstantAttributeGenerator(const T& value) :
		m_value(value)
	{

	}

	template<typename T>
	inline std::unique_ptr<AttributeGenerator<T>> ConstantAttributeGenerator<T>::clone() const
	{
		return std::make_unique<ConstantAttributeGenerator<T>>(*this);
	}

	template <typename T>
	class LinearAttributeGenerator : public AttributeGenerator<T>
	{
	private:
		T m_from;
		T m_to;

		T generateValue(unsigned int count, unsigned int index) const override;

	public:
		LinearAttributeGenerator(const T& from, const T& to);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T LinearAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index) const
	{
		float t = static_cast<float>(index) / static_cast<float>(count - 1);
		return (1.0f - t) * m_from + t * m_to;
	}

	template<typename T>
	inline LinearAttributeGenerator<T>::LinearAttributeGenerator(const T& from, const T& to) :
		m_from(from),
		m_to(to)
	{

	}

	template<typename T>
	inline std::unique_ptr<AttributeGenerator<T>> LinearAttributeGenerator<T>::clone() const
	{
		return std::make_unique<LinearAttributeGenerator<T>>(*this);
	}

	template <typename T>
	class RandomAttributeGenerator : public AttributeGenerator<T>
	{
	private:
		T m_minimum;
		T m_maximum;
		RandomNumberGenerator& m_randomNumberGenerator;

		T generateValue(unsigned int count, unsigned int index) const override;

	public:
		RandomAttributeGenerator(const T& minimum, const T& maximum, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T RandomAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index) const
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

	template <typename T>
	class RandomSetAttributeGenerator : public AttributeGenerator<T>
	{
	private:
		std::vector<T> m_values;
		RandomNumberGenerator& m_randomNumberGenerator;

		T generateValue(unsigned int count, unsigned int index) const override;

	public:
		RandomSetAttributeGenerator(const std::vector<T>& values, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T RandomSetAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index) const
	{
		if (m_values.empty())
			return T(0.0f);

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

	template <typename T>
	class SmoothRandomSetAttributeGenerator : public AttributeGenerator<T>
	{
	private:
		std::vector<T> m_values;
		RandomNumberGenerator& m_randomNumberGenerator;

		T generateValue(unsigned int count, unsigned int index) const override;

	public:
		SmoothRandomSetAttributeGenerator(const std::vector<T>& values, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T SmoothRandomSetAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index) const
	{
		if (m_values.empty())
			return T(0.0f);

		if (m_values.size() == 1)
			return m_values.front();

		unsigned int i = m_randomNumberGenerator.generateInteger(0, m_values.size() - 2);
		unsigned int j = i + 1;

		float t = m_randomNumberGenerator.generate(0.0f, 1.0f);
		return (1.0f - t) * m_values[i] + t * m_values[j];
	}

	template<typename T>
	inline SmoothRandomSetAttributeGenerator<T>::SmoothRandomSetAttributeGenerator(const std::vector<T>& values, RandomNumberGenerator& randomNumberGenerator) :
		m_values(values),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	template<typename T>
	inline std::unique_ptr<AttributeGenerator<T>> SmoothRandomSetAttributeGenerator<T>::clone() const
	{
		return std::make_unique<SmoothRandomSetAttributeGenerator<T>>(*this);
	}

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

		T generateValue(unsigned int count, unsigned int index) const override;

	public:
		WeightedRandomSetAttributeGenerator(const std::vector<WeightedValue>& values, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T WeightedRandomSetAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index) const
	{
		if (m_values.empty())
			return T(0.0f);

		unsigned int randomIndex = m_randomNumberGenerator.generateInteger(0, m_values.size() - 1);
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