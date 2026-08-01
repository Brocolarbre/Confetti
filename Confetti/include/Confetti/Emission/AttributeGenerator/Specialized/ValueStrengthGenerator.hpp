#pragma once

#include "Confetti/Export.hpp"
#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Emission/AttributeGenerator/AttributeTypes.hpp"

namespace cft
{
	class CONFETTI_API ValueStrengthGenerator : public AttributeGenerator<glm::vec3>
	{
	private:
		std::unique_ptr<AttributeGenerator<glm::vec3>> m_valueGenerator;
		std::unique_ptr<AttributeGenerator<float>> m_strengthGenerator;

		glm::vec3 generateValue(unsigned int count, unsigned int index, const SpawnContext& context, float elapsedTime) override;

	public:
		ValueStrengthGenerator(std::unique_ptr<AttributeGenerator<glm::vec3>> valueGenerator, std::unique_ptr<AttributeGenerator<float>> strengthGenerator);

		std::unique_ptr<AttributeGenerator<glm::vec3>> clone() const override;

		std::optional<std::uint64_t> getSeed() const override;
		void setSeed(std::uint64_t seed) override;

		std::vector<glm::vec3> generate(unsigned int count, const std::vector<SpawnContext>& context, float elapsedTime) override;
	};
}