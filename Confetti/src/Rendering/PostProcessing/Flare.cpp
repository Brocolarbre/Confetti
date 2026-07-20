#include "Confetti/Rendering/PostProcessing/Flare.hpp"
#include "Confetti/Rendering/ShaderSource/FlareShaderSource.hpp"
#include "Confetti/Rendering/ShaderSource/FullscreenShaderSource.hpp"

#include <glad/glad.h>

namespace cft
{
	void Flare::setupDownsampleShader(unsigned int mipLevel) const
	{
		m_downsampleShader.use();		
		m_downsampleShader.setUniform("uDirection", m_direction);
		m_downsampleShader.setUniform("uRadius", m_radius);
		m_downsampleShader.setUniform("uMipLevel", mipLevel);
	}

	void Flare::setupUpsampleShader(unsigned int mipLevel) const
	{
		m_upsampleShader.use();
		m_upsampleShader.setUniform("uDirection", m_direction);
		m_upsampleShader.setUniform("uRadius", m_radius);
		m_upsampleShader.setUniform("uChromaticAberrationStrength", m_chromaticAberrationStrength);
		m_upsampleShader.setUniform("uMipLevel", mipLevel);
	}

	Flare::Flare(unsigned int width, unsigned int height, unsigned int mipCount, const glm::vec2& direction, float radius, float chromaticAberrationStrength) :
		MipChainEffect(width, height, mipCount),
		m_downsampleShader(),
		m_upsampleShader(),
		m_direction(glm::normalize(direction)),
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
		m_direction = glm::normalize(direction);
	}

	void Flare::setRadius(float radius)
	{
		m_radius = glm::max(radius, 0.0f);
	}

	void Flare::setChromaticAberrationStength(float chromaticAberrationStrength)
	{
		m_chromaticAberrationStrength = glm::max(chromaticAberrationStrength, 0.0f);
	}
}