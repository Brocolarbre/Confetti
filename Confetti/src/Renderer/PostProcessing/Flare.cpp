#include "Confetti/Renderer/PostProcessing/Flare.hpp"
#include "Confetti/Renderer/ShaderSource/FlareShaderSource.hpp"
#include "Confetti/Renderer/ShaderSource/FullscreenShaderSource.hpp"

#include <glad/glad.h>

namespace cft
{
	Flare::Flare(unsigned int width, unsigned int height, float threshold, const glm::vec2& direction, int radius, float chromaticSeparationStrength) :
		m_brightPassFramebuffer(width, height),
		m_flareFramebuffer(width, height),
		m_brightPassShader(),
		m_flareShader(),
		m_vertexArray(0),
		m_threshold(threshold),
		m_direction(direction),
		m_radius(radius),
		m_chromaticSeparationStrength(chromaticSeparationStrength)
	{
		Texture brightPassColorAttachment(GL_TEXTURE_2D, GL_R11F_G11F_B10F, GL_RGB, GL_FLOAT);
		brightPassColorAttachment.load(nullptr, width, height, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, false);

		Texture flareColorAttachment(GL_TEXTURE_2D, GL_R11F_G11F_B10F, GL_RGB, GL_FLOAT);
		flareColorAttachment.load(nullptr, width, height, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, false);

		m_brightPassFramebuffer.setColorAttachment(0, std::move(brightPassColorAttachment));
		m_brightPassFramebuffer.build();

		m_flareFramebuffer.setColorAttachment(0, std::move(flareColorAttachment));
		m_flareFramebuffer.build();

		m_brightPassShader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, BRIGHT_PASS_FRAGMENT_SHADER_SOURCE);
		m_brightPassShader.use();
		m_brightPassShader.setUniform("uTexture", 0);

		m_flareShader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, FLARE_FRAGMENT_SHADER_SOURCE);
		m_flareShader.use();
		m_flareShader.setUniform("uTexture", 0);

		glGenVertexArrays(1, &m_vertexArray);
	}

	Flare::~Flare()
	{
		glDeleteVertexArrays(1, &m_vertexArray);
	}

	unsigned int Flare::getOutputTexture() const
	{
		return std::get<Texture>(m_flareFramebuffer.getColorAttachment(0)).getId();
	}

	void Flare::setThreshold(float threshold)
	{
		m_threshold = threshold;
	}

	void Flare::setDirection(const glm::vec2& direction)
	{
		m_direction = direction;
	}

	void Flare::setRadius(int radius)
	{
		m_radius = radius;
	}

	void Flare::setChromaticSeparationStength(float chromaticSeparationStrength)
	{
		m_chromaticSeparationStrength = chromaticSeparationStrength;
	}

	void Flare::resize(unsigned int width, unsigned int height)
	{
		m_brightPassFramebuffer.resize(width, height);
		m_flareFramebuffer.resize(width, height);
	}

	void Flare::render(unsigned int texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		m_brightPassFramebuffer.bind();
		m_brightPassFramebuffer.setViewport();
		m_brightPassFramebuffer.clear(GL_COLOR_BUFFER_BIT);

		m_brightPassShader.use();
		m_brightPassShader.setUniform("uThreshold", m_threshold);

		glBindVertexArray(m_vertexArray);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, std::get<Texture>(m_brightPassFramebuffer.getColorAttachment(0)).getId());

		m_flareFramebuffer.bind();
		m_flareFramebuffer.setViewport();
		m_flareFramebuffer.clear(GL_COLOR_BUFFER_BIT);

		m_flareShader.use();
		m_flareShader.setUniform("uDirection", m_direction);
		m_flareShader.setUniform("uRadius", m_radius);
		m_flareShader.setUniform("uChromaticSeparationStrength", m_chromaticSeparationStrength);

		glBindVertexArray(m_vertexArray);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}