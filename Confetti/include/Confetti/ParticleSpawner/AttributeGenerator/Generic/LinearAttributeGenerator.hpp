#pragma once

#include "Confetti/ParticleSpawner/AttributeGenerator/AttributeGenerator.hpp"

namespace cft
{
	template <typename T>
	class LinearAttributeGenerator : public AttributeGenerator<T>
	{
	private:
		T m_from;
		T m_to;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		LinearAttributeGenerator(const T& from, const T& to);

		std::unique_ptr<AttributeGenerator<T>> clone() const override;
	};

	template<typename T>
	inline T LinearAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
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
}