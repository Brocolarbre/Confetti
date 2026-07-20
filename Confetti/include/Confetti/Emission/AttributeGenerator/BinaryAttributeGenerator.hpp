#pragma once

#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"

namespace cft
{
	template <typename T, typename U>
	class BinaryAttributeGenerator : public AttributeGenerator<T>
	{
	public:
		using BinaryOperation = std::function<T(T, U)>;

	private:
		std::unique_ptr<AttributeGenerator<T>> m_leftOperand;
		std::unique_ptr<AttributeGenerator<U>> m_rightOperand;
		BinaryOperation m_operation;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		BinaryAttributeGenerator(std::unique_ptr<AttributeGenerator<T>> leftOperand, std::unique_ptr<AttributeGenerator<U>> rightOperand, BinaryOperation operation);

		std::vector<T> generate(unsigned int count, const std::vector<SpawnContext>& context) const override;
		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T, typename U>
	inline T BinaryAttributeGenerator<T, U>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
	{
		return T{};
	}

	template<typename T, typename U>
	inline BinaryAttributeGenerator<T, U>::BinaryAttributeGenerator(std::unique_ptr<AttributeGenerator<T>> leftOperand, std::unique_ptr<AttributeGenerator<U>> rightOperand, BinaryOperation operation) :
		m_leftOperand(std::move(leftOperand)),
		m_rightOperand(std::move(rightOperand)),
		m_operation(operation)
	{

	}

	template<typename T, typename U>
	inline std::vector<T> BinaryAttributeGenerator<T, U>::generate(unsigned int count, const std::vector<SpawnContext>& context) const
	{
		std::vector<T> leftOperand = m_leftOperand->generate(count, context);
		std::vector<U> rightOperand = m_rightOperand->generate(count, context);

		if (leftOperand.size() != count || rightOperand.size() != count)
			return {};

		for (unsigned int i = 0; i < count; ++i)
			leftOperand[i] = m_operation(leftOperand[i], rightOperand[i]);

		return leftOperand;
	}

	template<typename T, typename U>
	inline std::unique_ptr<AttributeGenerator<T>> BinaryAttributeGenerator<T, U>::clone() const
	{
		return std::make_unique<BinaryAttributeGenerator<T, U>>(m_leftOperand->clone(), m_rightOperand->clone(), m_operation);
	}
}