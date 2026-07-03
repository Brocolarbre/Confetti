#include "Confetti/Renderer/PostProcessing/Bloom.hpp"
#include "Confetti/Renderer/ShaderSource/BloomShaderSource.hpp"
#include "Confetti/Renderer/ShaderSource/FullscreenShaderSource.hpp"

#include <glad/glad.h>

namespace cft
{
	void Bloom::renderDownsamples(unsigned int sourceTexture)
	{
		const std::vector<Texture>& mips = m_bloomFramebuffer.getMips();

		m_downsampleShader.use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sourceTexture);

		for (const Texture& mip : mips)
		{
			glViewport(0, 0, mip.getWidth(), mip.getHeight());
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mip.getId(), 0);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_vertexArray);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			mip.bind();
		}
	}

	void Bloom::renderUpsamples(float filterRadius)
	{
		const std::vector<Texture>& mips = m_bloomFramebuffer.getMips();

		m_upsampleShader.use();
		m_upsampleShader.setUniform("uFilterRadius", filterRadius);

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);

		for (int i = static_cast<int>(mips.size()) - 1; i > 0; --i)
		{
			const Texture& mip = mips[i];
			const Texture& nextMip = mips[static_cast<size_t>(i) - 1];

			glActiveTexture(GL_TEXTURE0);
			mip.bind();

			glViewport(0, 0, nextMip.getWidth(), nextMip.getHeight());
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, nextMip.getId(), 0);

			glBindVertexArray(m_vertexArray);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}

		glDisable(GL_BLEND);
	}

	Bloom::Bloom(unsigned int width, unsigned int height, unsigned int mipCount, float filterRadius) :
		m_bloomFramebuffer(width, height, mipCount),
		m_downsampleShader(),
		m_upsampleShader(),
		m_vertexArray(0),
		m_filterRadius(filterRadius)
	{
		m_downsampleShader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, DOWNSAMPLE_FRAGMENT_SHADER_SOURCE);
		m_upsampleShader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, UPSAMPLE_FRAGMENT_SHADER_SOURCE);

		m_downsampleShader.use();
		m_downsampleShader.setUniform("uSourceTexture", 0);

		m_upsampleShader.use();
		m_upsampleShader.setUniform("uSourceTexture", 0);

		glGenVertexArrays(1, &m_vertexArray);
	}

	Bloom::~Bloom()
	{
		glDeleteVertexArrays(1, &m_vertexArray);
	}

	unsigned int Bloom::getOutputTexture() const
	{
		return m_bloomFramebuffer.getMips()[0].getId();
	}

	void Bloom::setFilterRadius(float filterRadius)
	{
		m_filterRadius = filterRadius;
	}

	void Bloom::resize(unsigned int width, unsigned int height)
	{
		m_bloomFramebuffer.resize(width, height);
	}

	void Bloom::render(unsigned int sourceTexture)
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		m_bloomFramebuffer.bind();

		renderDownsamples(sourceTexture);
		renderUpsamples(m_filterRadius);
	}
}