#include "Confetti/Renderer/Tools/Framebuffer.hpp"

#include <glad/glad.h>
#include <iostream>

namespace cft
{
	void Framebuffer::attachAttachment(const FramebufferAttachment& attachment, unsigned int attachmentPoint) const
	{
		glFramebufferTexture(GL_FRAMEBUFFER, attachmentPoint, 0, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentPoint, GL_RENDERBUFFER, 0);

		std::visit([&](const auto& value) {
			using T = std::decay_t<decltype(value)>;

			if constexpr (std::is_same_v<T, Texture>)
				glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentPoint, value.getTarget(), value.getId(), 0);
			else if constexpr (std::is_same_v<T, Renderbuffer>)
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentPoint, GL_RENDERBUFFER, value.getId());
			}, attachment);
	}

	void Framebuffer::resizeAttachment(FramebufferAttachment& attachment, unsigned int width, unsigned int height)
	{
		std::visit([&](auto& value) {
			if constexpr (std::is_same_v<std::decay_t<decltype(value)>, std::monostate>)
				return;
			else
				value.resize(width, height);
		}, attachment);
	}

	Framebuffer::Framebuffer(unsigned int width, unsigned int height) :
		m_id(0),
		m_width(width),
		m_height(height),
		m_colorAttachments(),
		m_depthAttachment(),
		m_stencilAttachment(),
		m_depthStencilAttachment()
	{
		glGenFramebuffers(1, &m_id);
	}

	Framebuffer::Framebuffer(Framebuffer&& framebuffer) noexcept :
		m_id(framebuffer.m_id),
		m_width(framebuffer.m_width),
		m_height(framebuffer.m_height),
		m_colorAttachments(std::move(framebuffer.m_colorAttachments)),
		m_depthAttachment(std::move(framebuffer.m_depthAttachment)),
		m_stencilAttachment(std::move(framebuffer.m_stencilAttachment)),
		m_depthStencilAttachment(std::move(framebuffer.m_depthStencilAttachment))
	{
		framebuffer.m_id = 0;
	}

	Framebuffer::~Framebuffer()
	{
		if (m_id != 0)
			glDeleteFramebuffers(1, &m_id);
	}

	Framebuffer& Framebuffer::operator=(Framebuffer&& framebuffer) noexcept
	{
		if (&framebuffer == this)
			return *this;

		if (m_id != 0)
			glDeleteFramebuffers(1, &m_id);

		m_id = framebuffer.m_id;
		m_width = framebuffer.m_width;
		m_height = framebuffer.m_height;
		m_colorAttachments = std::move(framebuffer.m_colorAttachments);
		m_depthAttachment = std::move(framebuffer.m_depthAttachment);
		m_stencilAttachment = std::move(framebuffer.m_stencilAttachment);
		m_depthStencilAttachment = std::move(framebuffer.m_depthStencilAttachment);

		framebuffer.m_id = 0;

		return *this;
	}

	unsigned int Framebuffer::getId() const
	{
		return m_id;
	}

	unsigned int Framebuffer::getWidth() const
	{
		return m_width;
	}

	unsigned int Framebuffer::getHeight() const
	{
		return m_height;
	}

	const FramebufferAttachment& Framebuffer::getColorAttachment(unsigned int index) const
	{
		return m_colorAttachments[index];
	}

	const FramebufferAttachment& Framebuffer::getDepthAttachment() const
	{
		return m_depthAttachment;
	}

	const FramebufferAttachment& Framebuffer::getStencilAttachment() const
	{
		return m_stencilAttachment;
	}

	const FramebufferAttachment& Framebuffer::getDepthStencilAttachment() const
	{
		return m_depthStencilAttachment;
	}

	void Framebuffer::setColorAttachment(unsigned int index, FramebufferAttachment attachment)
	{
		if (index > MAXIMUM_COLOR_ATTACHMENTS - 1)
		{
			std::cerr << "Framebuffer error : cannot have more than " << MAXIMUM_COLOR_ATTACHMENTS << " color attachments" << std::endl;
			return;
		}

		if (index == m_colorAttachments.size())
			m_colorAttachments.push_back(std::move(attachment));
		else if (index < m_colorAttachments.size())
			m_colorAttachments[index] = std::move(attachment);
		else
			std::cerr << "Framebuffer error : color attachment indices must grow one by one starting from 0" << std::endl;
	}

	void Framebuffer::setDepthAttachment(FramebufferAttachment attachment)
	{
		m_depthAttachment = std::move(attachment);
	}

	void Framebuffer::setStencilAttachment(FramebufferAttachment attachment)
	{
		m_stencilAttachment = std::move(attachment);
	}

	void Framebuffer::setDepthStencilAttachment(FramebufferAttachment attachment)
	{
		m_depthStencilAttachment = std::move(attachment);
	}

	bool Framebuffer::build()
	{
		if (m_colorAttachments.empty() && std::holds_alternative<std::monostate>(m_depthAttachment) && std::holds_alternative<std::monostate>(m_stencilAttachment))
		{
			std::cerr << "Framebuffer error : cannot have a framebuffer with no attachments" << std::endl;
			return false;
		}

		if (!std::holds_alternative<std::monostate>(m_depthAttachment) && !std::holds_alternative<std::monostate>(m_stencilAttachment))
		{
			std::cerr << "Framebuffer error : cannot have both depth and stencil attachments in the same framebuffer" << std::endl;
			return false;
		}

		if (!std::holds_alternative<std::monostate>(m_depthStencilAttachment) && (!std::holds_alternative<std::monostate>(m_depthAttachment) || !std::holds_alternative<std::monostate>(m_stencilAttachment)))
		{
			std::cerr << "Framebuffer error : cannot have both depth or stencil attachments and depth stencil attachment in the same framebuffer" << std::endl;
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, m_id);

		std::vector<unsigned int> drawBuffers;
		drawBuffers.reserve(m_colorAttachments.size());

		for (unsigned int i = 0; i < m_colorAttachments.size(); ++i)
		{
			unsigned int drawBuffer = GL_COLOR_ATTACHMENT0 + i;
			drawBuffers.push_back(drawBuffer);

			attachAttachment(m_colorAttachments[i], drawBuffer);
		}

		glDrawBuffers(static_cast<unsigned int>(drawBuffers.size()), drawBuffers.data());

		if (m_colorAttachments.empty())
		{
			glReadBuffer(GL_NONE);
			glDrawBuffer(GL_NONE);
		}

		attachAttachment(m_depthAttachment, GL_DEPTH_ATTACHMENT);
		attachAttachment(m_stencilAttachment, GL_STENCIL_ATTACHMENT);
		attachAttachment(m_depthStencilAttachment, GL_DEPTH_STENCIL_ATTACHMENT);

		unsigned int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cerr << "Framebuffer error : framebuffer incomplete" << std::endl;
			return false;
		}

		return true;
	}

	void Framebuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	}

	void Framebuffer::setViewport() const
	{
		glViewport(0, 0, m_width, m_height);
	}

	void Framebuffer::resize(unsigned int width, unsigned int height)
	{
		m_width = width;
		m_height = height;

		for (unsigned int i = 0; i < m_colorAttachments.size(); ++i)
			resizeAttachment(m_colorAttachments[i], width, height);

		resizeAttachment(m_depthAttachment, width, height);
		resizeAttachment(m_stencilAttachment, width, height);
		resizeAttachment(m_depthStencilAttachment, width, height);
	}

	void Framebuffer::clear(unsigned int mask, float r, float g, float b, float a, double depth, int stencil) const
	{
		if (mask != 0)
		{
			glClearColor(r, g, b, a);
			glClearDepth(depth);
			glClearStencil(stencil);
			glClear(mask);
		}
	}

	void Framebuffer::copy(const Framebuffer& destination, unsigned int mask, std::optional<unsigned int> sourceColorAttachmentIndex, std::optional<unsigned int> destinationColorAttachmentIndex) const
	{
		if (sourceColorAttachmentIndex.has_value() && std::holds_alternative<std::monostate>(m_colorAttachments[sourceColorAttachmentIndex.value()]) || destinationColorAttachmentIndex.has_value() && std::holds_alternative<std::monostate>(destination.m_colorAttachments[destinationColorAttachmentIndex.value()]))
		{
			std::cerr << "Framebuffer error : invalid color attachment index for copy" << std::endl;
			return;
		}

		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id);
		glReadBuffer(sourceColorAttachmentIndex.has_value() ? GL_COLOR_ATTACHMENT0 + sourceColorAttachmentIndex.value() : GL_NONE);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, destination.getId());
		glDrawBuffer(destinationColorAttachmentIndex.has_value() ? GL_COLOR_ATTACHMENT0 + destinationColorAttachmentIndex.value() : GL_NONE);

		glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, destination.getWidth(), destination.getHeight(), mask, GL_NEAREST);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}
}