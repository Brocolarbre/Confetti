#include "Confetti/Renderer/PostProcessing/BloomFramebuffer.hpp"

#include <glad/glad.h>
#include <iostream>

namespace cft
{
	BloomFramebuffer::BloomFramebuffer(unsigned int width, unsigned int height, unsigned int mipCount) :
		m_id(0),
		m_mipCount(mipCount),
		m_mips()
	{
		glGenFramebuffers(1, &m_id);

		resize(width, height);
	}

	BloomFramebuffer::~BloomFramebuffer()
	{
		glDeleteFramebuffers(1, &m_id);
	}

	const std::vector<Texture>& BloomFramebuffer::getMips() const
	{
		return m_mips;
	}

	void BloomFramebuffer::resize(unsigned int width, unsigned int height)
	{
		m_mips.clear();
		m_mips.reserve(m_mipCount);

		glm::uvec2 mipSize(width, height);
		for (unsigned int i = 0; i < m_mipCount; ++i)
		{
			mipSize.x = std::max(1u, mipSize.x / 2);
			mipSize.y = std::max(1u, mipSize.y / 2);

			Texture mip(GL_TEXTURE_2D, GL_R11F_G11F_B10F, GL_RGB, GL_FLOAT);
			mip.load(nullptr, mipSize.x, mipSize.y, GL_LINEAR, GL_CLAMP_TO_EDGE, false);

			m_mips.push_back(std::move(mip));
		}

		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_mips[0].getId(), 0);

		unsigned int drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawBuffers);

		int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << "Bloom framebuffer incomplete" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void BloomFramebuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	}
}