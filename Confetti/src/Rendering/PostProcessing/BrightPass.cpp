#include "Confetti/Rendering/PostProcessing/BrightPass.hpp"
#include "Confetti/Rendering/ShaderSource/BrightPassShaderSource.hpp"
#include "Confetti/Rendering/ShaderSource/FullscreenShaderSource.hpp"

#include <glad/glad.h>

namespace cft
{
	BrightPass::BrightPass(unsigned int width, unsigned int height, float threshold) :
		m_framebuffer(width, height),
		m_shader(),
		m_vertexArray(0),
		m_threshold(threshold)
	{
		Texture colorAttachment(GL_TEXTURE_2D, GL_R11F_G11F_B10F, GL_RGB, GL_FLOAT);
		colorAttachment.load(nullptr, width, height, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, false);

		m_framebuffer.setColorAttachment(0, std::move(colorAttachment));
		m_framebuffer.build();

		m_shader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, BRIGHT_PASS_FRAGMENT_SHADER_SOURCE);
		m_shader.use();
		m_shader.setUniform("uTexture", 0);

		glGenVertexArrays(1, &m_vertexArray);
	}

	BrightPass::~BrightPass()
	{
		if (m_vertexArray != 0)
			glDeleteVertexArrays(1, &m_vertexArray);
	}

	unsigned int BrightPass::getOutputTexture() const
	{
		return std::get<Texture>(m_framebuffer.getColorAttachment(0)).getId();
	}

	void BrightPass::setThreshold(float threshold)
	{
		m_threshold = threshold;
	}

	void BrightPass::resize(unsigned int width, unsigned int height)
	{
		m_framebuffer.resize(width, height);
	}

	void BrightPass::render(unsigned int texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		m_framebuffer.bind();

		m_shader.use();
		m_shader.setUniform("uThreshold", m_threshold);

		glBindVertexArray(m_vertexArray);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}