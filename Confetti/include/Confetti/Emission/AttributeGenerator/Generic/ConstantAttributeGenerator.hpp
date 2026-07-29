#pragma once

#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"

namespace cft
{
	template <typename T>
	class ConstantAttributeGenerator : public Cloneable<ConstantAttributeGenerator<T>, AttributeGenerator<T>>
	{
	private:
		T m_value;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) override;

	public:
		ConstantAttributeGenerator(const T& value);
	};

	template <typename T>
	inline T ConstantAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context)
	{
		return m_value;
	}

	template <typename T>
	inline ConstantAttributeGenerator<T>::ConstantAttributeGenerator(const T& value) :
		m_value(value)
	{

	}
}