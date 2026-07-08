#include "Confetti/Renderer/PostProcessing/MipChainFramebuffer.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>

namespace cft
{
	MipChainFramebuffer::MipChainFramebuffer(unsigned int width, unsigned int height, unsigned int mipCount, unsigned int internalFormat, unsigned int format, unsigned int type) :
		m_id(0),
		m_mips(),
		m_mipCount(mipCount),
		m_internalFormat(internalFormat),
		m_format(format),
		m_type(type)
	{
		glGenFramebuffers(1, &m_id);

		resize(width, height);
	}

	MipChainFramebuffer::MipChainFramebuffer(MipChainFramebuffer&& mipChainFramebuffer) noexcept :
		m_id(mipChainFramebuffer.m_id),
		m_mips(std::move(mipChainFramebuffer.m_mips)),
		m_mipCount(mipChainFramebuffer.m_mipCount),
		m_internalFormat(mipChainFramebuffer.m_internalFormat),
		m_format(mipChainFramebuffer.m_format),
		m_type(mipChainFramebuffer.m_type)
	{
		mipChainFramebuffer.m_id = 0;
	}

	MipChainFramebuffer::~MipChainFramebuffer()
	{
		if (m_id != 0)
			glDeleteFramebuffers(1, &m_id);
	}

	MipChainFramebuffer& MipChainFramebuffer::operator=(MipChainFramebuffer&& mipChainFramebuffer) noexcept
	{
		if (&mipChainFramebuffer == this)
			return *this;

		if (m_id != 0)
			glDeleteFramebuffers(1, &m_id);

		m_id = mipChainFramebuffer.m_id;
		m_mips = std::move(mipChainFramebuffer.m_mips);
		m_mipCount = mipChainFramebuffer.m_mipCount;
		m_internalFormat = mipChainFramebuffer.m_internalFormat;
		m_format = mipChainFramebuffer.m_format;
		m_type = mipChainFramebuffer.m_type;

		mipChainFramebuffer.m_id = 0;

		return *this;
	}

	const std::vector<Texture>& MipChainFramebuffer::getMips() const
	{
		return m_mips;
	}

	unsigned int MipChainFramebuffer::getOutputTexture() const
	{
		return m_mips.front().getId();
	}

	void MipChainFramebuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	}

	void MipChainFramebuffer::resize(unsigned int width, unsigned int height)
	{
		if (m_mipCount == 0)
		{
			std::cerr << "Mip chain framebuffer error : cannot have a mip count of 0" << std::endl;
			return;
		}

		m_mips.clear();
		m_mips.reserve(m_mipCount);

		glm::uvec2 mipSize(width, height);
		for (unsigned int i = 0; i < m_mipCount; ++i)
		{
			mipSize.x = std::max(1u, mipSize.x / 2);
			mipSize.y = std::max(1u, mipSize.y / 2);

			Texture mip(GL_TEXTURE_2D, m_internalFormat, m_format, m_type);
			float borderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
			mip.load(nullptr, mipSize.x, mipSize.y, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_BORDER, false);

			m_mips.push_back(std::move(mip));
		}

		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_mips[0].getId(), 0);

		unsigned int drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawBuffers);

		int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << "Mip chain framebuffer incomplete" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}