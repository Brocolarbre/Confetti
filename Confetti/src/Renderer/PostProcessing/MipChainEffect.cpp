#include "Confetti/Renderer/PostProcessing/MipChainEffect.hpp"
#include "Confetti/Renderer/ShaderSource/FullscreenShaderSource.hpp"

#include <glad/glad.h>

namespace cft
{
	void MipChainEffect::renderDownsamples(unsigned int sourceTexture) const
	{
		const std::vector<Texture>& mips = m_framebuffer.getMips();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sourceTexture);

		for (unsigned mip = 0; mip < mips.size(); ++mip)
		{
			setupDownsampleShader(mip);

			glViewport(0, 0, mips[mip].getWidth(), mips[mip].getHeight());
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mips[mip].getId(), 0);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_vertexArray);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			mips[mip].bind();
		}
	}

	void MipChainEffect::renderUpsamples() const
	{
		const std::vector<Texture>& mips = m_framebuffer.getMips();

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);

		glActiveTexture(GL_TEXTURE0);
		for (int mip = static_cast<int>(mips.size()) - 1; mip > 0; --mip)
		{
			setupUpsampleShader(mip);

			const Texture& currentMip = mips[mip];
			const Texture& nextMip = mips[static_cast<size_t>(mip) - 1];

			currentMip.bind();

			glViewport(0, 0, nextMip.getWidth(), nextMip.getHeight());
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, nextMip.getId(), 0);

			glBindVertexArray(m_vertexArray);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}

		glDisable(GL_BLEND);
	}

	MipChainEffect::MipChainEffect(unsigned int width, unsigned int height, unsigned int mipCount) :
		m_framebuffer(width, height, mipCount, GL_R11F_G11F_B10F, GL_RGB, GL_FLOAT),
		m_vertexArray(0)
	{
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