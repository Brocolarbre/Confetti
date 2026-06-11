#include "Confetti/Renderer/Tools/TextureArray.hpp"

#include <glad/glad.h>

namespace cft
{
	TextureArray::TextureArray(unsigned int internalFormat, unsigned int format, unsigned int type) :
		m_id(0),
		m_width(0),
		m_height(0),
		m_internalFormat(internalFormat),
		m_format(format),
		m_type(type)
	{
		glGenTextures(1, &m_id);
	}

	TextureArray::TextureArray(TextureArray&& textureArray) noexcept :
		m_id(textureArray.m_id),
		m_width(textureArray.m_width),
		m_height(textureArray.m_height),
		m_internalFormat(textureArray.m_internalFormat),
		m_format(textureArray.m_format),
		m_type(textureArray.m_type)
	{
		textureArray.m_id = 0;
	}

	TextureArray::~TextureArray()
	{
		if (m_id != 0)
			glDeleteTextures(1, &m_id);
	}

	TextureArray& TextureArray::operator=(TextureArray&& textureArray) noexcept
	{
		if (m_id != 0)
			glDeleteTextures(1, &m_id);

		m_id = textureArray.m_id;
		m_width = textureArray.m_width;
		m_height = textureArray.m_height;
		m_internalFormat = textureArray.m_internalFormat;
		m_format = textureArray.m_format;
		m_type = textureArray.m_type;

		textureArray.m_id = 0;

		return *this;
	}

	unsigned int TextureArray::getId() const
	{
		return m_id;
	}

	unsigned int TextureArray::getWidth() const
	{
		return m_width;
	}

	unsigned int TextureArray::getHeight() const
	{
		return m_height;
	}

	void TextureArray::bind() const
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_id);
	}

	void TextureArray::load(const std::vector<const void*>& data, unsigned int width, unsigned int height, unsigned int filtering, unsigned int wrapping)
	{
		if (data.empty())
			return;

		m_width = width;
		m_height = height;

		glBindTexture(GL_TEXTURE_2D_ARRAY, m_id);
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, m_internalFormat, width, height, data.size());

		for (unsigned int layer = 0; layer < data.size(); ++layer)
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer, width, height, 1, m_format, m_type, data[layer]);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, filtering);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, filtering);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, wrapping);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, wrapping);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, wrapping);

		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

	void TextureArray::setActiveSlot(unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
	}
}