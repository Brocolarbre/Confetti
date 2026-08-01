#include "Confetti/Emission/AttributeGenerator/Specialized/ValueStrengthGenerator.hpp"

namespace cft
{
	glm::vec3 ValueStrengthGenerator::generateValue(unsigned int count, unsigned int index, const SpawnContext& context, float elapsedTime)
	{
		return {};
	}

	ValueStrengthGenerator::ValueStrengthGenerator(std::unique_ptr<AttributeGenerator<glm::vec3>> valueGenerator, std::unique_ptr<AttributeGenerator<float>> strengthGenerator) :
		m_valueGenerator(std::move(valueGenerator)),
		m_strengthGenerator(std::move(strengthGenerator))
	{

	}

	std::unique_ptr<AttributeGenerator<glm::vec3>> ValueStrengthGenerator::clone() const
	{
		return std::make_unique<ValueStrengthGenerator>(m_valueGenerator->clone(), m_strengthGenerator->clone());
	}

	std::optional<std::uint64_t> ValueStrengthGenerator::getSeed() const
	{
		return m_valueGenerator->getSeed();
	}

	void ValueStrengthGenerator::setSeed(std::uint64_t seed)
	{
		m_valueGenerator->setSeed(seed);
		m_strengthGenerator->setSeed(seed);
	}

	std::vector<glm::vec3> ValueStrengthGenerator::generate(unsigned int count, const std::vector<SpawnContext>& context, float elapsedTime)
	{
		std::vector<glm::vec3> value = m_valueGenerator->generate(count, context, elapsedTime);
		std::vector<float> strength = m_strengthGenerator->generate(count, context, elapsedTime);

		if (value.size() != count || strength.size() != count)
			return {};

		for (unsigned int i = 0; i < count; i++)
			value[i] *= strength[i];

		return value;
	}
}