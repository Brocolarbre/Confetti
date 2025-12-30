#include "ConfettiEngine/Renderer/Renderer.hpp"

#include <glad/glad.h>
#include <iostream>

namespace cft
{
	bool Renderer::m_intialized = false;

	Renderer::Renderer(unsigned int width, unsigned int height) :
		m_framebuffer(width, height),
		m_shader(),
		m_mesh(),
		m_ssbo(100), // dynamique
		m_width(width),
		m_height(height)
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	unsigned int Renderer::getOutputTextureId() const
	{
		return m_framebuffer.getColorAttachment();
	}

	void Renderer::resize(unsigned int width, unsigned int height)
	{
		m_framebuffer.resize(width, height);
		m_width = width;
		m_height = height;
	}

	void Renderer::render(const View& view, const ParticlePool& particlePool) const
	{
		while (GLenum error = glGetError())
			std::cerr << "OpenGL error : " << error << std::endl;

		m_ssbo.setData(particlePool);

		m_framebuffer.bind();
		glViewport(0, 0, m_width, m_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_ssbo.bind();

		m_shader.use();
		m_shader.setUniform("uView", view.viewMatrix);
		m_shader.setUniform("uProjection", view.projectionMatrix);

		m_mesh.drawInstanced(particlePool.count);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	bool Renderer::initialize(void* loader)
	{
		if (m_intialized)
			return true;

		if(gladLoadGLLoader(static_cast<GLADloadproc>(loader)))
			m_intialized = true;

		return m_intialized;
	}
}