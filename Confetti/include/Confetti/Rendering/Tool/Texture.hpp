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
		unsigned int m_samples;

	public:
		Texture(unsigned int target, unsigned int internalFormat, int format, unsigned int type, unsigned int samples = 1);
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
		void load(const void* data, unsigned int width, unsigned int height, unsigned int minFilter, unsigned int magFilter, unsigned int wrapping, bool mipmaps);
		void resize(unsigned int width, unsigned int height);

		static void setActiveSlot(unsigned int slot);
	};
}