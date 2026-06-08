#include "Confetti/Renderer/Renderer.hpp"

#include <glad/glad.h>

#include <thread>

namespace cft
{
	Renderer::Renderer(unsigned int width, unsigned int height) :
		m_width(width),
		m_height(height),
		m_framebuffer(width, height),
		m_shader(),
		m_mesh(),
		m_ssbo(),
		m_bloom(width, height, 5)
	{
		
	}

	unsigned int Renderer::getOutputTextureId() const
	{
		return m_bloom.getBloomTexture();
		//return m_framebuffer.getColorAttachment();
	}

	void Renderer::resize(unsigned int width, unsigned int height)
	{
		m_framebuffer.resize(width, height);
		m_width = width;
		m_height = height;

		m_bloom.resize(width, height);
	}

	void Renderer::render(const View& view, const std::unordered_map<unsigned int, ParticlePool>& particlePools)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		std::vector<std::reference_wrapper<const cft::ParticlePool>> pools;
		pools.reserve(particlePools.size());

		for (const auto& [id, pool] : particlePools)
			pools.push_back(pool);

		unsigned int totalParticleCount = 0;
		for (const auto& pool : pools)
			totalParticleCount += pool.get().getCount();

		m_ssbo.setData(pools, totalParticleCount);

		m_framebuffer.bind();
		glViewport(0, 0, m_width, m_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_ssbo.bind();

		m_shader.use();
		m_shader.setUniform("uView", view.viewMatrix);
		m_shader.setUniform("uProjection", view.projectionMatrix);

		m_mesh.drawInstanced(totalParticleCount);

		m_bloom.render(m_framebuffer.getColorAttachment(), 0.005f);
	}
}