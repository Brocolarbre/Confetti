#include "Confetti/Renderer/PostProcessing/ToneMapping.hpp"
#include "Confetti/Renderer/ShaderSource/ToneMappingShaderSource.hpp"
#include "Confetti/Renderer/ShaderSource/FullscreenShaderSource.hpp"

#include <glad/glad.h>

namespace cft
{
	ToneMapping::ToneMapping(unsigned int width, unsigned int height, float exposure, float gamma) :
		m_framebuffer(width, height),
		m_shader(),
		m_vertexArray(0),
		m_exposure(exposure),
		m_gamma(gamma)
	{
		Texture colorAttachment(GL_TEXTURE_2D, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		colorAttachment.load(nullptr, width, height, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, false);

		m_framebuffer.setColorAttachment(0, std::move(colorAttachment));
		m_framebuffer.build();

		m_shader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, TONEMAPPING_FRAGMENT_SHADER_SOURCE);
		m_shader.use();
		m_shader.setUniform("uTexture", 0);

		glGenVertexArrays(1, &m_vertexArray);
	}

	ToneMapping::~ToneMapping()
	{
		glDeleteVertexArrays(1, &m_vertexArray);
	}

	unsigned int ToneMapping::getOutputTexture() const
	{
		return std::get<Texture>(m_framebuffer.getColorAttachment(0)).getId();
	}

	void ToneMapping::setExposure(float exposure)
	{
		m_exposure = exposure;
	}

	void ToneMapping::setGamma(float gamma)
	{
		m_gamma = gamma;
	}

	void ToneMapping::resize(unsigned int width, unsigned int height)
	{
		m_framebuffer.resize(width, height);
	}

	void ToneMapping::render(unsigned int texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		m_framebuffer.bind();

		m_shader.use();
		m_shader.setUniform("uExposure", m_exposure);
		m_shader.setUniform("uGamma", m_gamma);

		glBindVertexArray(m_vertexArray);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}