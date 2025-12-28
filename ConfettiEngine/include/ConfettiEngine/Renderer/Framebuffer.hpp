#pragma once

namespace cft
{
	class Framebuffer
	{
	private:
		unsigned int m_id;
		unsigned int m_colorAttachment;
		unsigned int m_depthAttachment;

	public:
		Framebuffer(unsigned int width, unsigned int height);
		~Framebuffer();

		unsigned int getId() const;
		unsigned int getColorAttachment() const;

		void resize(unsigned int width, unsigned int height) const;
		void bind() const;
	};
}