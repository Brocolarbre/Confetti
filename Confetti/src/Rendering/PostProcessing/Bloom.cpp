#include "Confetti/Rendering/PostProcessing/Bloom.hpp"
#include "Confetti/Rendering/ShaderSource/BloomShaderSource.hpp"
#include "Confetti/Rendering/ShaderSource/FullscreenShaderSource.hpp"

namespace cft
{
	void Bloom::setupDownsampleShader(unsigned int mipLevel) const
	{
		m_downsampleShader.use();
		m_downsampleShader.setUniform("uFilterRadius", m_filterRadius);
	}

	void Bloom::setupUpsampleShader(unsigned int mipLevel) const
	{
		m_upsampleShader.use();
		m_upsampleShader.setUniform("uFilterRadius", m_filterRadius);
	}

	Bloom::Bloom(unsigned int width, unsigned int height, unsigned int mipCount, float filterRadius) :
		MipChainEffect(width, height, mipCount),
		m_downsampleShader(),
		m_upsampleShader(),
		m_filterRadius(filterRadius)
	{
		m_downsampleShader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, BLOOM_DOWNSAMPLE_FRAGMENT_SHADER_SOURCE);
		m_upsampleShader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, BLOOM_UPSAMPLE_FRAGMENT_SHADER_SOURCE);

		m_downsampleShader.use();
		m_downsampleShader.setUniform("uTexture", 0);

		m_upsampleShader.use();
		m_upsampleShader.setUniform("uTexture", 0);
	}

	void Bloom::setFilterRadius(float filterRadius)
	{
		m_filterRadius = filterRadius;
	}
}