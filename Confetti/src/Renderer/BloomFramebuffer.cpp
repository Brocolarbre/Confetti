#include "Confetti/Renderer/BloomFramebuffer.hpp"

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
		for (const BloomMip& mip : m_mips)
			glDeleteTextures(1, &mip.texture);

		glDeleteFramebuffers(1, &m_id);
	}

	const std::vector<BloomMip>& BloomFramebuffer::getMips() const
	{
		return m_mips;
	}

	void BloomFramebuffer::resize(unsigned int width, unsigned int height)
	{
		for (const BloomMip& mip : m_mips)
			glDeleteTextures(1, &mip.texture);

		m_mips.clear();
		m_mips.reserve(m_mipCount);

		glm::vec2 mipSize(width, height);
		for (unsigned int i = 0; i < m_mipCount; ++i)
		{
			BloomMip mip{};

			mipSize.x = std::max(1.0f, mipSize.x * 0.5f);
			mipSize.y = std::max(1.0f, mipSize.y * 0.5f);
			mip.size = mipSize;

			glGenTextures(1, &mip.texture);
			glBindTexture(GL_TEXTURE_2D, mip.texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_R11F_G11F_B10F, static_cast<unsigned int>(mipSize.x), static_cast<unsigned int>(mipSize.y), 0, GL_RGB, GL_FLOAT, nullptr);

			m_mips.push_back(mip);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_mips[0].texture, 0);

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