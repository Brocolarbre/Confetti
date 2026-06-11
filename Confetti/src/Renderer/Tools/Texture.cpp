#include "Confetti/Renderer/Tools/Texture.hpp"

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <iostream>

namespace cft
{
	Texture::Texture(unsigned int target, unsigned int internalFormat, int format, unsigned int type, unsigned int samples) :
		m_id(0),
		m_width(0),
		m_height(0),
		m_target(target),
		m_format(format),
		m_internalFormat(internalFormat),
		m_type(type),
		m_samples(glm::max(samples, 1u))
	{
		glGenTextures(1, &m_id);
	}

	Texture::Texture(Texture&& texture) noexcept :
		m_id(texture.m_id),
		m_width(texture.m_width),
		m_height(texture.m_height),
		m_target(texture.m_target),
		m_format(texture.m_format),
		m_internalFormat(texture.m_internalFormat),
		m_type(texture.m_type),
		m_samples(texture.m_samples)
	{
		texture.m_id = 0;
	}

	Texture::~Texture()
	{
		if (m_id != 0)
			glDeleteTextures(1, &m_id);
	}

	Texture& Texture::operator=(Texture&& texture) noexcept
	{
		if (this == &texture)
			return *this;

		if (m_id != 0)
			glDeleteTextures(1, &m_id);

		m_id = texture.m_id;
		m_width = texture.m_width;
		m_height = texture.m_height;
		m_target = texture.m_target;
		m_internalFormat = texture.m_internalFormat;
		m_format = texture.m_format;
		m_type = texture.m_type;
		m_samples = texture.m_samples;

		texture.m_id = 0;

		return *this;
	}

	unsigned int Texture::getId() const
	{
		return m_id;
	}

	unsigned int Texture::getWidth() const
	{
		return m_width;
	}

	unsigned int Texture::getHeight() const
	{
		return m_height;
	}

	unsigned int Texture::getTarget() const
	{
		return m_target;
	}

	void Texture::bind() const
	{
		glBindTexture(m_target, m_id);
	}

	void Texture::resize(unsigned int width, unsigned int height)
	{
		m_width = width;
		m_height = height;

		glBindTexture(m_target, m_id);

		if (m_samples > 1)
			glTexImage2DMultisample(m_target, m_samples, m_internalFormat, m_width, m_height, GL_TRUE);
		else
			glTexImage2D(m_target, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, nullptr);

		glBindTexture(m_target, 0);
	}

	void Texture::load(const void* data, unsigned int width, unsigned int height, unsigned int filtering, unsigned int wrapping, bool mipmaps, unsigned int level)
	{
		if (m_samples > 1 && data != nullptr)
		{
			std::cerr << "Texture error : Cannot upload data to a multisampled texture" << std::endl;
			return;
		}

		m_width = width;
		m_height = height;

		glBindTexture(m_target, m_id);
		if (m_samples > 1)
		{
			glTexImage2DMultisample(m_target, m_samples, m_internalFormat, m_width, m_height, GL_TRUE);
		}
		else
		{
			glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, filtering);
			glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, filtering);
			glTexParameteri(m_target, GL_TEXTURE_WRAP_S, wrapping);
			glTexParameteri(m_target, GL_TEXTURE_WRAP_T, wrapping);

			glTexImage2D(m_target, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, data);
		}

		if (mipmaps)
			glGenerateMipmap(m_target);

		glBindTexture(m_target, 0);
	}

	void Texture::setActiveSlot(unsigned int slot)
	{
		if (slot > 15)
		{
			std::cerr << "Texture error : cannot bind texture to a slot at index above 15" << std::endl;
			return;
		}

		glActiveTexture(GL_TEXTURE0 + slot);
	}
}