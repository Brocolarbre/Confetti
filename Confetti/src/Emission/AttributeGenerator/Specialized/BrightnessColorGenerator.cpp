#include "Confetti/Emission/AttributeGenerator/Specialized/BrightnessColorGenerator.hpp"

namespace cft
{
	Color BrightnessColorGenerator::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
	{
		return {};
	}

	BrightnessColorGenerator::BrightnessColorGenerator(std::unique_ptr<AttributeGenerator<Color>> colorGenerator, std::unique_ptr<AttributeGenerator<float>> brightnessGenerator) :
		m_colorGenerator(std::move(colorGenerator)),
		m_brightnessGenerator(std::move(brightnessGenerator))
	{

	}

	std::vector<Color> BrightnessColorGenerator::generate(unsigned int count, const std::vector<SpawnContext>& context) const
	{
		std::vector<Color> color = m_colorGenerator->generate(count, context);
		std::vector<float> brightness = m_brightnessGenerator->generate(count, context);

		if (color.size() != count || brightness.size() != count)
			return {};

		for (unsigned int i = 0; i < count; i++)
		{
			color[i].r *= brightness[i];
			color[i].g *= brightness[i];
			color[i].b *= brightness[i];
		}

		return color;
	}

	std::unique_ptr<AttributeGenerator<Color>> BrightnessColorGenerator::clone() const
	{
		return std::make_unique<BrightnessColorGenerator>(m_colorGenerator->clone(), m_brightnessGenerator->clone());
	}
}