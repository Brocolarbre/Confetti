#pragma once

namespace cft
{
	class Renderbuffer
	{
	private:
		unsigned int m_id;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_internalFormat;
		unsigned int m_samples;

	public:
		Renderbuffer(unsigned int internalFormat, unsigned int samples = 1);
		Renderbuffer(const Renderbuffer& renderbuffer) = delete;
		Renderbuffer(Renderbuffer&& renderbuffer) noexcept;
		~Renderbuffer();

		Renderbuffer& operator=(const Renderbuffer& renderbuffer) = delete;
		Renderbuffer& operator=(Renderbuffer&& renderbuffer) noexcept;

		unsigned int getId() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;

		void bind() const;
		void load(unsigned int width, unsigned int height);
		void resize(unsigned int width, unsigned int height);
	};
}