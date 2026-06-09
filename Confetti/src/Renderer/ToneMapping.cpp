#include "Confetti/Renderer/ToneMapping.hpp"
#include "Confetti/Renderer/ShaderSource.hpp"

#include <glad/glad.h>

namespace cft
{
	ToneMapping::ToneMapping(float exposure, float gamma) :
		m_shader(),
		m_vertexArray(0),
		m_exposure(exposure),
		m_gamma(gamma)
	{
		m_shader.loadFromMemory(SAMPLE_VERTEX_SHADER_SOURCE, TONEMAPPING_FRAGMENT_SHADER_SOURCE);
		m_shader.use();
		m_shader.setUniform("uTexture", 0);

		glGenVertexArrays(1, &m_vertexArray);
	}

	ToneMapping::~ToneMapping()
	{
		glDeleteVertexArrays(1, &m_vertexArray);
	}

	void ToneMapping::setExposure(float exposure)
	{
		m_exposure = exposure;
	}

	void ToneMapping::setGamme(float gamma)
	{
		m_gamma = gamma;
	}

	void ToneMapping::render(unsigned int texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		m_shader.use();
		m_shader.setUniform("uExposure", m_exposure);
		m_shader.setUniform("uGamma", m_gamma);

		glBindVertexArray(m_vertexArray);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}