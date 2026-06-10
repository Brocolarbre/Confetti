#include "Confetti/Renderer/Tools/RenderBuffer.hpp"

#include <glad/glad.h>

namespace cft
{
	Renderbuffer::Renderbuffer(unsigned int internalFormat) :
		m_id(0),
		m_width(0),
		m_height(0),
		m_internalFormat(internalFormat)
	{
		glGenRenderbuffers(1, &m_id);
	}

	Renderbuffer::Renderbuffer(Renderbuffer&& renderbuffer) noexcept :
		m_id(renderbuffer.m_id),
		m_width(renderbuffer.m_width),
		m_height(renderbuffer.m_height),
		m_internalFormat(renderbuffer.m_internalFormat)
	{
		renderbuffer.m_id = 0;
	}

	Renderbuffer::~Renderbuffer()
	{
		if (m_id != 0)
			glDeleteRenderbuffers(1, &m_id);
	}

	Renderbuffer& Renderbuffer::operator=(Renderbuffer&& renderbuffer) noexcept
	{
		if (this == &renderbuffer)
			return *this;

		if (m_id != 0)
			glDeleteRenderbuffers(1, &m_id);

		m_id = renderbuffer.m_id;
		m_width = renderbuffer.m_width;
		m_height = renderbuffer.m_height;
		m_internalFormat = renderbuffer.m_internalFormat;

		renderbuffer.m_id = 0;

		return *this;
	}

	unsigned int Renderbuffer::getId() const
	{
		return m_id;
	}

	unsigned int Renderbuffer::getWidth() const
	{
		return m_width;
	}

	unsigned int Renderbuffer::getHeight() const
	{
		return m_height;
	}

	void Renderbuffer::bind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_id);
	}

	void Renderbuffer::load(unsigned int width, unsigned int height)
	{
		m_width = width;
		m_height = height;

		glBindRenderbuffer(GL_RENDERBUFFER, m_id);
		glRenderbufferStorage(GL_RENDERBUFFER, m_internalFormat, m_width, m_height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void Renderbuffer::resize(unsigned int width, unsigned int height)
	{
		load(width, height);
	}
}