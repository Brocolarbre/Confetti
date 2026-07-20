#pragma once

#include <vector>

namespace cft
{
	class TextureArray
	{
	private:
		unsigned int m_id;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_internalFormat;
		unsigned int m_format;
		unsigned int m_type;

	public:
		TextureArray(unsigned int internalFormat, unsigned int format, unsigned int type);
		TextureArray(const TextureArray& textureArray) = delete;
		TextureArray(TextureArray&& textureArray) noexcept;
		~TextureArray();

		TextureArray& operator=(const TextureArray& textureArray) = delete;
		TextureArray& operator=(TextureArray&& textureArray) noexcept;

		unsigned int getId() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;

		void bind() const;
		void load(const std::vector<const void*>& data, unsigned int width, unsigned int height, unsigned int filtering, unsigned int wrapping);
		
		static void setActiveSlot(unsigned int slot);
	};
}