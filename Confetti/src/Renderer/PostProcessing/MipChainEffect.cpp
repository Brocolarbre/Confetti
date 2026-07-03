#include "Confetti/Renderer/PostProcessing/MipChainEffect.hpp"
#include "Confetti/Renderer/ShaderSource/DownsampleShaderSource.hpp"
#include "Confetti/Renderer/ShaderSource/FullscreenShaderSource.hpp"

#include <glad/glad.h>

namespace cft
{
	void MipChainEffect::renderDownsamples(unsigned int sourceTexture) const
	{
		const std::vector<Texture>& mips = m_framebuffer.getMips();

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

	void MipChainEffect::renderUpsamples() const
	{
		const std::vector<Texture>& mips = m_framebuffer.getMips();

		setupUpsampleShader();

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);

		glActiveTexture(GL_TEXTURE0);

		for (int i = static_cast<int>(mips.size()) - 1; i > 0; --i)
		{
			const Texture& mip = mips[i];
			const Texture& nextMip = mips[static_cast<size_t>(i) - 1];

			mip.bind();

			glViewport(0, 0, nextMip.getWidth(), nextMip.getHeight());
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, nextMip.getId(), 0);
			// check if this needs to be added
			//glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_vertexArray);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}

		glDisable(GL_BLEND);
		// check this too
		//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	}

	MipChainEffect::MipChainEffect(unsigned int width, unsigned int height, unsigned int mipCount) :
		m_framebuffer(width, height, mipCount, GL_R11F_G11F_B10F, GL_RGB, GL_FLOAT),
		m_downsampleShader(),
		m_vertexArray(0)
	{
		m_downsampleShader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, DOWNSAMPLE_FRAGMENT_SHADER_SOURCE);

		m_downsampleShader.use();
		m_downsampleShader.setUniform("uTexture", 0);

		glGenVertexArrays(1, &m_vertexArray);
	}

	MipChainEffect::~MipChainEffect()
	{
		if (m_vertexArray != 0)
			glDeleteVertexArrays(1, &m_vertexArray);
	}

	unsigned int MipChainEffect::getOutputTexture() const
	{
		return m_framebuffer.getOutputTexture();
	}

	void MipChainEffect::resize(unsigned int width, unsigned int height)
	{
		m_framebuffer.resize(width, height);
	}

	void MipChainEffect::render(unsigned int sourceTexture) const
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		m_framebuffer.bind();

		renderDownsamples(sourceTexture);
		renderUpsamples();
	}
}