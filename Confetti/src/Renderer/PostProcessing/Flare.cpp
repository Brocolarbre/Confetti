#include "Confetti/Renderer/PostProcessing/Flare.hpp"
#include "Confetti/Renderer/ShaderSource/FlareShaderSource.hpp"
#include "Confetti/Renderer/ShaderSource/FullscreenShaderSource.hpp"

#include <glad/glad.h>

namespace cft
{
	void Flare::setupDownsampleShader(unsigned int mipLevel) const
	{
		m_downsampleShader.use();		
		m_downsampleShader.setUniform("uDirection", m_direction);
	}

	void Flare::setupUpsampleShader(unsigned int mipLevel) const
	{
		m_upsampleShader.use();
		m_upsampleShader.setUniform("uDirection", m_direction);
		//m_upsampleShader.setUniform("uRadius", m_radius * std::pow(2.0f, static_cast<float>(mipLevel) * 0.5f));
		//m_upsampleShader.setUniform("uRadius", m_radius * std::pow(1.5f, static_cast<float>(mipLevel)));
		m_upsampleShader.setUniform("uRadius", m_radius * (1.0f + mipLevel));
		m_upsampleShader.setUniform("uChromaticAberrationStrength", m_chromaticAberrationStrength);

	}

	Flare::Flare(unsigned int width, unsigned int height, unsigned int mipCount, const glm::vec2& direction, float radius, float chromaticAberrationStrength) :
		MipChainEffect(width, height, mipCount),
		m_downsampleShader(),
		m_upsampleShader(),
		m_direction(direction),
		m_radius(radius),
		m_chromaticAberrationStrength(chromaticAberrationStrength)
	{
		m_downsampleShader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, FLARE_DOWNSAMPLE_FRAGMENT_SHADER_SOURCE);
		m_upsampleShader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, FLARE_UPSAMPLE_FRAGMENT_SHADER_SOURCE);

		m_downsampleShader.use();
		m_downsampleShader.setUniform("uTexture", 0);

		m_upsampleShader.use();
		m_upsampleShader.setUniform("uTexture", 0);
	}


	void Flare::setDirection(const glm::vec2& direction)
	{
		m_direction = direction;
	}

	void Flare::setRadius(float radius)
	{
		m_radius = radius;
	}

	void Flare::setChromaticAberrationStength(float chromaticAberrationStrength)
	{
		m_chromaticAberrationStrength = chromaticAberrationStrength;
	}
}