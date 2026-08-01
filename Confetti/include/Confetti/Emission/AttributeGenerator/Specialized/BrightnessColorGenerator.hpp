#pragma once

#include "Confetti/Export.hpp"
#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"
#include "Confetti/Emission/AttributeGenerator/AttributeTypes.hpp"

namespace cft
{
	class CONFETTI_API BrightnessColorGenerator : public AttributeGenerator<Color>
	{
	private:
		std::unique_ptr<AttributeGenerator<Color>> m_colorGenerator;
		std::unique_ptr<AttributeGenerator<float>> m_brightnessGenerator;

		Color generateValue(unsigned int count, unsigned int index, const SpawnContext& context, float elapsedTime) override;

	public:
		BrightnessColorGenerator(std::unique_ptr<AttributeGenerator<Color>> colorGenerator, std::unique_ptr<AttributeGenerator<float>> brightnessGenerator);

		std::unique_ptr<AttributeGenerator<Color>> clone() const override;

		std::optional<std::uint64_t> getSeed() const override;
		void setSeed(std::uint64_t seed) override;

		std::vector<Color> generate(unsigned int count, const std::vector<SpawnContext>& context, float elapsedTime) override;
	};
}