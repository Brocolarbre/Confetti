#include "Confetti/Rendering/PostProcessing/HdrComposite.hpp"
#include "Confetti/Rendering/ShaderSource/HdrCompositeShaderSource.hpp"
#include "Confetti/Rendering/ShaderSource/FullscreenShaderSource.hpp"

#include <glad/glad.h>

namespace cft
{
	HdrComposite::HdrComposite(unsigned int width, unsigned int height, float bloomStrength, float flareStrength) :
		m_framebuffer(width, height),
		m_shader(),
		m_vertexArray(0),
		m_bloomStrength(bloomStrength),
		m_flareStrength(flareStrength)
	{
		Texture colorAttachment(GL_TEXTURE_2D, GL_R11F_G11F_B10F, GL_RGB, GL_FLOAT);
		colorAttachment.load(nullptr, width, height, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, false);

		m_framebuffer.setColorAttachment(0, std::move(colorAttachment));
		m_framebuffer.build();

		m_shader.loadFromMemory(FULLSCREEN_VERTEX_SHADER_SOURCE, HDR_COMPOSITE_FRAGMENT_SHADER_SOURCE);
		m_shader.use();
		m_shader.setUniform("uSourceTexture", 0);
		m_shader.setUniform("uBloomTexture", 1);
		m_shader.setUniform("uFlareTexture", 2);

		glGenVertexArrays(1, &m_vertexArray);
	}

	HdrComposite::~HdrComposite()
	{
		glDeleteVertexArrays(1, &m_vertexArray);
	}

	unsigned int HdrComposite::getOutputTexture() const
	{
		return std::get<Texture>(m_framebuffer.getColorAttachment(0)).getId();
	}

	void HdrComposite::setBloomStrength(float bloomStrength)
	{
		m_bloomStrength = bloomStrength;
	}

	void HdrComposite::setFlareStrength(float flareStrength)
	{
		m_flareStrength = flareStrength;
	}

	void HdrComposite::resize(unsigned int width, unsigned int height)
	{
		m_framebuffer.resize(width, height);
	}

	void HdrComposite::render(unsigned int sourceTexture, unsigned int bloomTexture, unsigned int flareTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sourceTexture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, bloomTexture);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, flareTexture);

		m_framebuffer.bind();
		m_framebuffer.setViewport();
		m_framebuffer.clear(GL_COLOR_BUFFER_BIT);

		m_shader.use();
		m_shader.setUniform("uBloomStrength", m_bloomStrength);
		m_shader.setUniform("uFlareStrength", m_flareStrength);

		glBindVertexArray(m_vertexArray);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}