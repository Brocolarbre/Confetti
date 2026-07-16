#include "Confetti/Renderer/ParticleRenderer.hpp"

#include <glad/glad.h>

namespace cft
{
	ParticleRenderer::ParticleRenderer(unsigned int width, unsigned int height, unsigned int samples) :
		m_width(width),
		m_height(height),
		m_framebuffer(width, height),
		m_resolvedFramebuffer(width, height),
		m_bloom(width, height, 5, 0.005f),
		m_brightPass(width, height, 2.0f),
		m_flare(width, height, 5, glm::vec2(1.0f, 0.0f), 0.8f, 0.05f),
		m_hdrComposite(width, height, 0.04f, 0.5f),
		m_toneMapping(width, height, 0.25f, 2.2f),
		m_billboardParticleRenderer(),
		m_meshParticleRenderer(),
		m_trailRenderer()
	{
		Texture colorAttachment(GL_TEXTURE_2D_MULTISAMPLE, GL_RGBA16F, GL_RGBA, GL_FLOAT, samples);
		colorAttachment.load(nullptr, m_width, m_height, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, false);

		Renderbuffer depthAttachment(GL_DEPTH_COMPONENT, samples);
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
		return std::get<Texture>(m_resolvedFramebuffer.getColorAttachment(0)).getId();
		return m_toneMapping.getOutputTexture();
	}

	void ParticleRenderer::loadBillboardRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height)
	{
		m_billboardParticleRenderer.loadTextures(assetRegistry, imageIds, width, height);
	}

	void ParticleRenderer::loadMeshRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds)
	{
		m_meshParticleRenderer.loadTextures(assetRegistry, imageIds);
	}

	void ParticleRenderer::loadMeshRendererMeshes(AssetRegistry& assetRegistry, const std::vector<unsigned int>& modelIds)
	{
		m_meshParticleRenderer.loadMeshes(assetRegistry, modelIds);
	}

	void ParticleRenderer::loadTrailRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height)
	{
		m_trailRenderer.loadTextures(assetRegistry, imageIds, width, height);
	}

	void ParticleRenderer::resize(unsigned int width, unsigned int height)
	{
		m_width = width;
		m_height = height;

		m_framebuffer.resize(width, height);
		m_resolvedFramebuffer.resize(width, height);

		m_bloom.resize(width, height);
		m_brightPass.resize(width, height);
		m_flare.resize(width, height);
		m_hdrComposite.resize(width, height);
		m_toneMapping.resize(width, height);
	}

	void ParticleRenderer::update(const ParticleSimulation& particleSimulation, const AssetRegistry& assetRegistry, const View& view)
	{
		m_billboardParticleRenderer.update(particleSimulation.getParticlePools(), particleSimulation.getParticleRegistry(), assetRegistry);
		m_meshParticleRenderer.update(particleSimulation.getParticlePools(), particleSimulation.getParticleRegistry());
		m_trailRenderer.update(particleSimulation.getTrailPools(), particleSimulation.getTrailRegistry(), particleSimulation.getRibbonPools(), particleSimulation.getRibbonRegistry(), view);
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

		unsigned int hdrSceneTexture = std::get<Texture>(m_resolvedFramebuffer.getColorAttachment(0)).getId();

		glDisable(GL_BLEND);
		
		m_bloom.render(hdrSceneTexture);
		glViewport(0, 0, m_width, m_height);
		m_brightPass.render(hdrSceneTexture);
		m_flare.render(m_brightPass.getOutputTexture());
		glViewport(0, 0, m_width, m_height);

		m_hdrComposite.render(hdrSceneTexture, m_bloom.getOutputTexture(), m_flare.getOutputTexture());
		m_toneMapping.render(m_hdrComposite.getOutputTexture());
	}
}