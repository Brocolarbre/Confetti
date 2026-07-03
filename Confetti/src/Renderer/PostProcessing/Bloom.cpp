#include "Confetti/Renderer/PostProcessing/Bloom.hpp"
#include "Confetti/Renderer/ShaderSource/BloomShaderSource.hpp"
#include "Confetti/Renderer/ShaderSource/FullscreenShaderSource.hpp"

namespace cft
{
	void Bloom::setupUpsampleShader() const
	{
		m_upsampleShader.use();
		m_upsampleShader.setUniform("uFilterRadius", m_filterRadius);
	}

	Bloom::Bloom(unsigned int width, unsigned int height, unsigned int mipCount, float filterRadius) :
		MipChainEffect(width, height, mipCount),
		m_upsampleShader(),
		m_filterRadius(filterRadius)
	{
		m_upsampleShader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, BLOOM_UPSAMPLE_FRAGMENT_SHADER_SOURCE);

		m_upsampleShader.use();
		m_upsampleShader.setUniform("uTexture", 0);
	}

	void Bloom::setFilterRadius(float filterRadius)
	{
		m_filterRadius = filterRadius;
	}
}