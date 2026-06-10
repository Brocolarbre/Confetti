#pragma once

namespace cft
{
	class Texture
	{
	private:
		unsigned int m_id;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_target;
		unsigned int m_internalFormat;
		unsigned int m_format;
		unsigned int m_type;

	public:
		Texture(unsigned int target, unsigned int internalFormat, int format, unsigned int type);
		Texture(const Texture& texture) = delete;
		Texture(Texture&& texture) noexcept;
		~Texture();

		Texture& operator=(const Texture& texture) = delete;
		Texture& operator=(Texture&& texture) noexcept;

		unsigned int getId() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		unsigned int getTarget() const;

		void bind() const;
		void load(const void* data, unsigned int width, unsigned int height, unsigned int filtering, unsigned int wrapping, bool mipmaps, unsigned int level);
		void resize(unsigned int width, unsigned int height);

		static void setActiveSlot(unsigned int slot);
	};
}