#include "Confetti/Renderer/ParticleRenderer.hpp"

#include <glad/glad.h>
#include <iostream>

namespace cft
{
	ParticleRenderer::ParticleRenderer(unsigned int width, unsigned int height) :
		m_width(width),
		m_height(height),
		m_framebuffer(width, height),
		m_resolvedFramebuffer(width, height),
		m_bloom(width, height, 5),
		m_toneMapping(width, height, 0.25f, 2.2f),
		m_billboardParticleRenderer(),
		m_meshParticleRenderer(),
		m_trailRenderer()
	{
		constexpr unsigned int SAMPLES = 4;

		Texture colorAttachment(GL_TEXTURE_2D_MULTISAMPLE, GL_RGBA16F, GL_RGBA, GL_FLOAT, SAMPLES);
		colorAttachment.load(nullptr, m_width, m_height, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, false);

		Renderbuffer depthAttachment(GL_DEPTH_COMPONENT, SAMPLES);
		depthAttachment.load(m_width, m_height);

		m_framebuffer.setColorAttachment(0, std::move(colorAttachment));
		m_framebuffer.setDepthAttachment(std::move(depthAttachment));
		m_framebuffer.build();

		Texture resolvedColorAttachment(GL_TEXTURE_2D, GL_RGBA16F, GL_RGBA, GL_FLOAT);
		resolvedColorAttachment.load(nullptr, m_width, m_height, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, false);

		m_resolvedFramebuffer.setColorAttachment(0, std::move(resolvedColorAttachment));
		m_resolvedFramebuffer.build();
	}

	unsigned int ParticleRenderer::getOutputTextureId() const
	{
		//return std::get<Texture>(m_resolvedFramebuffer.getColorAttachment(0)).getId();
		return m_toneMapping.getOutputTexture();
	}

	void ParticleRenderer::loadBillboardRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& images, unsigned int width, unsigned int height)
	{
		m_billboardParticleRenderer.loadTextures(assetRegistry, images, width, height);
	}

	void ParticleRenderer::loadMeshRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& images)
	{
		m_meshParticleRenderer.loadTextures(assetRegistry, images);
	}

	void ParticleRenderer::loadMeshRendererMeshes(AssetRegistry& assetRegistry, const std::vector<unsigned int>& models)
	{
		m_meshParticleRenderer.loadMeshes(assetRegistry, models);
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

	void ParticleRenderer::update(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const std::unordered_map<unsigned int, TrailPool>& trailPools, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry, const View& view)
	{
		m_billboardParticleRenderer.update(particlePools, particleRegistry, assetRegistry);
		m_meshParticleRenderer.update(particlePools, particleRegistry);
		m_trailRenderer.update(trailPools, view);
	}

	void ParticleRenderer::render(const View& view, float elapsedTime, const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry)
	{
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		m_framebuffer.bind();
		glViewport(0, 0, m_width, m_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_trailRenderer.render(view);
		m_billboardParticleRenderer.render(view, elapsedTime);
		m_meshParticleRenderer.render(view);
		
		m_framebuffer.copy(m_resolvedFramebuffer, GL_COLOR_BUFFER_BIT, 0, 0);

		m_bloom.render(std::get<Texture>(m_resolvedFramebuffer.getColorAttachment(0)).getId(), 0.005f);
		m_toneMapping.render(m_bloom.getBloomTexture().getId());
	}
}