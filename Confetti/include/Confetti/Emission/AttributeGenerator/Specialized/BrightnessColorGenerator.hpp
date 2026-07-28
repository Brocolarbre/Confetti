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

		Color generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const override;

	public:
		BrightnessColorGenerator(std::unique_ptr<AttributeGenerator<Color>> colorGenerator, std::unique_ptr<AttributeGenerator<float>> brightnessGenerator);

		std::vector<Color> generate(unsigned int count, const std::vector<SpawnContext>& context) const override;

		std::unique_ptr<AttributeGenerator<Color>> clone() const override;
	};
}