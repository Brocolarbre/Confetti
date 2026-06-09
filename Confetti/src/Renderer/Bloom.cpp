#include "Confetti/Renderer/Bloom.hpp"
#include "Confetti/Renderer/ShaderSource.hpp"

#include <glad/glad.h>


//
#include <iostream>

namespace cft
{
	void Bloom::renderDownsamples(unsigned int sourceTexture)
	{
		const std::vector<BloomMip>& mips = m_bloomFramebuffer.getMips();

		m_downsampleShader.use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sourceTexture);

		for (int i = 0; i < mips.size(); ++i)
		{
			const BloomMip& mip = mips[i];

			glViewport(0, 0, mip.size.x, mip.size.y);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mip.texture, 0);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_vertexArray);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			glBindTexture(GL_TEXTURE_2D, mip.texture);
		}
	}

	void Bloom::renderUpsamples(float filterRadius)
	{
		const std::vector<BloomMip>& mips = m_bloomFramebuffer.getMips();

		m_upsampleShader.use();
		m_upsampleShader.setUniform("uFilterRadius", filterRadius);

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);

		for (int i = static_cast<int>(mips.size()) - 1; i > 0; --i)
		{
			const BloomMip& mip = mips[i];
			const BloomMip& nextMip = mips[static_cast<size_t>(i) - 1];

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mip.texture);

			glViewport(0, 0, nextMip.size.x, nextMip.size.y);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, nextMip.texture, 0);

			glBindVertexArray(m_vertexArray);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}

		glDisable(GL_BLEND);
	}

	void Bloom::applyBloom(unsigned int sourceTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sourceTexture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_bloomFramebuffer.getMips()[0].texture);

		m_framebuffer.bind();
		glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);
		glClear(GL_COLOR_BUFFER_BIT);

		m_bloomShader.use();
		m_bloomShader.setUniform("uBloomStrength", 0.04f);

		glBindVertexArray(m_vertexArray);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	Bloom::Bloom(unsigned int width, unsigned int height, unsigned int mipCount) :
		m_bloomFramebuffer(width, height, mipCount),
		m_framebuffer(width, height),
		m_downsampleShader(),
		m_upsampleShader(),
		m_bloomShader(),
		m_mipCount(mipCount),
		m_viewportSize(width, height),
		m_vertexArray(0)
	{
		m_downsampleShader.loadFromMemory(SAMPLE_VERTEX_SHADER_SOURCE, DOWNSAMPLE_FRAGMENT_SHADER_SOURCE);
		m_upsampleShader.loadFromMemory(SAMPLE_VERTEX_SHADER_SOURCE, UPSAMPLE_FRAGMENT_SHADER_SOURCE);
		m_bloomShader.loadFromMemory(SAMPLE_VERTEX_SHADER_SOURCE, BLOOM_FRAGMENT_SHADER_SOURCE);

		m_downsampleShader.use();
		m_downsampleShader.setUniform("uSourceTexture", 0);

		m_upsampleShader.use();
		m_upsampleShader.setUniform("uSourceTexture", 0);

		m_bloomShader.use();
		m_bloomShader.setUniform("uSourceTexture", 0);
		m_bloomShader.setUniform("uBloomTexture", 1);

		glGenVertexArrays(1, &m_vertexArray);
	}

	Bloom::~Bloom()
	{
		glDeleteVertexArrays(1, &m_vertexArray);
	}

	unsigned int Bloom::getBloomTexture() const
	{
		return m_framebuffer.getColorAttachment();
	}

	void Bloom::resize(unsigned int width, unsigned int height)
	{
		m_bloomFramebuffer.resize(width, height);
		m_framebuffer.resize(width, height);
		m_viewportSize = glm::uvec2(width, height);
	}

	void Bloom::render(unsigned int sourceTexture, float filterRadius)
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		m_bloomFramebuffer.bind();

		renderDownsamples(sourceTexture);
		renderUpsamples(filterRadius);
		applyBloom(sourceTexture);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);
	}
}