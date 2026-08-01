#include "Confetti/Emission/AttributeGenerator/Specialized/BrightnessColorGenerator.hpp"

namespace cft
{
	Color BrightnessColorGenerator::generateValue(unsigned int count, unsigned int index, const SpawnContext& context, float elapsedTime)
	{
		return {};
	}

	BrightnessColorGenerator::BrightnessColorGenerator(std::unique_ptr<AttributeGenerator<Color>> colorGenerator, std::unique_ptr<AttributeGenerator<float>> brightnessGenerator) :
		m_colorGenerator(std::move(colorGenerator)),
		m_brightnessGenerator(std::move(brightnessGenerator))
	{

	}

	std::unique_ptr<AttributeGenerator<Color>> BrightnessColorGenerator::clone() const
	{
		return std::make_unique<BrightnessColorGenerator>(m_colorGenerator->clone(), m_brightnessGenerator->clone());
	}

	std::optional<std::uint64_t> BrightnessColorGenerator::getSeed() const
	{
		return m_colorGenerator->getSeed();
	}

	void BrightnessColorGenerator::setSeed(std::uint64_t seed)
	{
		m_colorGenerator->setSeed(seed);
		m_brightnessGenerator->setSeed(seed);
	}

	std::vector<Color> BrightnessColorGenerator::generate(unsigned int count, const std::vector<SpawnContext>& context, float elapsedTime)
	{
		std::vector<Color> color = m_colorGenerator->generate(count, context, elapsedTime);
		std::vector<float> brightness = m_brightnessGenerator->generate(count, context, elapsedTime);

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
}