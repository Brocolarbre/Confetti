#pragma once

#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"

#include <functional>

namespace cft
{
	template <typename T>
	class UnaryAttributeGenerator : public AttributeGenerator<T>
	{
	public:
		using UnaryOperation = std::function<T(T)>;

	private:
		std::unique_ptr<AttributeGenerator<T>> m_operand;
		UnaryOperation m_operation;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		UnaryAttributeGenerator(std::unique_ptr<AttributeGenerator<T>> operand, UnaryOperation operation);

		std::vector<T> generate(unsigned int count, const std::vector<SpawnContext>& context) const override;
		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T UnaryAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
	{
		return T{};
	}

	template<typename T>
	inline UnaryAttributeGenerator<T>::UnaryAttributeGenerator(std::unique_ptr<AttributeGenerator<T>> operand, UnaryOperation operation) :
		m_operand(std::move(operand)),
		m_operation(operation)
	{

	}

	template<typename T>
	inline std::vector<T> UnaryAttributeGenerator<T>::generate(unsigned int count, const std::vector<SpawnContext>& context) const
	{
		std::vector<T> operand = m_operand->generate(count, context);

		if (operand.size() != count)
			return {};

		for (unsigned int i = 0; i < count; ++i)
			operand[i] = m_operation(operand[i]);

		return operand;
	}

	template<typename T>
	inline std::unique_ptr<AttributeGenerator<T>> UnaryAttributeGenerator<T>::clone() const
	{
		return std::make_unique<UnaryAttributeGenerator<T, Operation>>(m_operand->clone(), m_operation);
	}
}