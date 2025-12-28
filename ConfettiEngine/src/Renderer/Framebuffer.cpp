#include "ConfettiEngine/Renderer/Framebuffer.hpp"

#include <glad/glad.h>
#include <iostream>

namespace cft
{
	Framebuffer::Framebuffer(unsigned int width, unsigned int height) :
		m_id(0),
		m_colorAttachment(0),
		m_depthAttachment(0)
	{
		if (width == 0 || height == 0)
		{
			std::cerr << "Invalid framebuffer size : (" << width << ", " << height << std::endl;
			return;
		}

		glGenFramebuffers(1, &m_id);
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);

		glGenTextures(1, &m_colorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_colorAttachment);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);

		glGenRenderbuffers(1, &m_depthAttachment);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthAttachment);

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthAttachment);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cerr << "Incomplete framebuffer" << std::endl;
			return;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_id);
		glDeleteTextures(1, &m_colorAttachment);
		glDeleteRenderbuffers(1, &m_depthAttachment);
	}

	unsigned int Framebuffer::getId() const
	{
		return m_id;
	}

	unsigned int Framebuffer::getColorAttachment() const
	{
		return m_colorAttachment;
	}

	void Framebuffer::resize(unsigned int width, unsigned int height) const
	{
		glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		glBindRenderbuffer(GL_RENDERBUFFER, m_depthAttachment);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	}

	void Framebuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	}
}