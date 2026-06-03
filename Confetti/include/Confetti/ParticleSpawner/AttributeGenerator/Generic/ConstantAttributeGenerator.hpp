#pragma once

#include "Confetti/ParticleSpawner/AttributeGenerator/AttributeGenerator.hpp"

namespace cft
{
	template <typename T>
	class ConstantAttributeGenerator : public AttributeGenerator<T>
	{
	private:
		T m_value;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		ConstantAttributeGenerator(const T& value);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T ConstantAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
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
}