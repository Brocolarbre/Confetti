#pragma once

#include "RenderBuffer.hpp"
#include "Texture.hpp"

#include <optional>
#include <variant>
#include <vector>

namespace cft
{
	using FramebufferAttachment = std::variant<std::monostate, Texture, Renderbuffer>;
	constexpr unsigned int MAXIMUM_COLOR_ATTACHMENTS = 16;

	class Framebuffer
	{
	private:
		unsigned int m_id;
		unsigned int m_width;
		unsigned int m_height;

		std::vector<FramebufferAttachment> m_colorAttachments;
		FramebufferAttachment m_depthAttachment;
		FramebufferAttachment m_stencilAttachment;
		FramebufferAttachment m_depthStencilAttachment;

		void attachAttachment(const FramebufferAttachment& attachment, unsigned int attachmentPoint) const;
		void resizeAttachment(FramebufferAttachment& attachment, unsigned int width, unsigned int height);

	public:
		Framebuffer(unsigned int width, unsigned int height);
		Framebuffer(const Framebuffer& framebuffer) = delete;
		Framebuffer(Framebuffer&& framebuffer) noexcept;
		~Framebuffer();

		Framebuffer& operator=(const Framebuffer& framebuffer) = delete;
		Framebuffer& operator=(Framebuffer&& framebuffer) noexcept;

		unsigned int getId() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;

		const FramebufferAttachment& getColorAttachment(unsigned int index) const;
		const FramebufferAttachment& getDepthAttachment() const;
		const FramebufferAttachment& getStencilAttachment() const;
		const FramebufferAttachment& getDepthStencilAttachment() const;

		void setColorAttachment(unsigned int index, FramebufferAttachment attachment);
		void setDepthAttachment(FramebufferAttachment attachment);
		void setStencilAttachment(FramebufferAttachment attachment);
		void setDepthStencilAttachment(FramebufferAttachment attachment);

		bool build();
		void bind() const;
		void setViewport() const;
		void resize(unsigned int width, unsigned int height);
		void clear(unsigned int mask, float r = 0.0, float g = 0.0, float b = 0.0, float a = 0.0, double depth = 1.0, int stencil = 0) const;
		void copy(const Framebuffer& destination, unsigned int mask, std::optional<unsigned int> sourceColorAttachmentIndex, std::optional<unsigned int> destinationColorAttachmentIndex) const;
	};
}