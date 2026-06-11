#include "Confetti/Renderer/Particle/ParticleRenderer.hpp"

#include <glad/glad.h>

namespace cft
{
	ParticleRenderer::ParticleRenderer(unsigned int width, unsigned int height) :
		m_width(width),
		m_height(height),
		m_framebuffer(width, height),
		m_resolvedFramebuffer(width, height),
		m_shader(),
		m_mesh(),
		m_ssbo(),
		m_bloom(width, height, 5),
		m_toneMapping(width, height, 0.25f, 2.2f)
	{
		constexpr unsigned int SAMPLES = 4;

		Texture colorAttachment(GL_TEXTURE_2D_MULTISAMPLE, GL_RGBA16F, GL_RGBA, GL_FLOAT, SAMPLES);
		colorAttachment.load(nullptr, m_width, m_height, GL_LINEAR, GL_CLAMP_TO_EDGE, false, 0);

		Renderbuffer depthAttachment(GL_DEPTH_COMPONENT, SAMPLES);
		depthAttachment.load(m_width, m_height);

		m_framebuffer.setColorAttachment(0, std::move(colorAttachment));
		m_framebuffer.setDepthAttachment(std::move(depthAttachment));
		m_framebuffer.build();

		Texture resolvedColorAttachment(GL_TEXTURE_2D, GL_RGBA16F, GL_RGBA, GL_FLOAT);
		resolvedColorAttachment.load(nullptr, m_width, m_height, GL_LINEAR, GL_CLAMP_TO_EDGE, false, 0);

		m_resolvedFramebuffer.setColorAttachment(0, std::move(resolvedColorAttachment));
		m_resolvedFramebuffer.build();
	}

	unsigned int ParticleRenderer::getOutputTextureId() const
	{
		//return std::get<Texture>(m_framebuffer.getColorAttachment(0)).getId();
		return m_toneMapping.getOutputTexture();
	}

	void ParticleRenderer::resize(unsigned int width, unsigned int height)
	{
		m_width = width;
		m_height = height;

		m_framebuffer.resize(width, height);
		m_resolvedFramebuffer.resize(width, height);

		m_bloom.resize(width, height);
		m_toneMapping.resize(width, height);
	}

	void ParticleRenderer::render(const View& view, const std::unordered_map<unsigned int, ParticlePool>& particlePools)
	{		
		glEnable(GL_MULTISAMPLE);
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
		
		m_framebuffer.copy(m_resolvedFramebuffer, GL_COLOR_BUFFER_BIT, 0, 0);

		m_bloom.render(std::get<Texture>(m_resolvedFramebuffer.getColorAttachment(0)).getId(), 0.005f);
		m_toneMapping.render(m_bloom.getBloomTexture().getId());
	}
}