#include "Confetti/Rendering/ParticleRenderer.hpp"

#include <glad/glad.h>

namespace cft
{
	bool ParticleRenderer::m_initialized = false;

	ParticleRenderer::ParticleRenderer(unsigned int width, unsigned int height, unsigned int samples, unsigned int mipCount) :
		m_width(width),
		m_height(height),
		m_framebuffer(width, height),
		m_resolvedFramebuffer(width, height),
		m_bloom(width, height, mipCount, 0.005f),
		m_brightPass(width, height, 2.0f),
		m_flare(width, height, mipCount, glm::vec2(1.0f, 0.0f), 0.8f, 0.05f),
		m_hdrComposite(width, height, 0.04f, 0.5f),
		m_toneMapping(width, height, 0.25f, 2.2f),
		m_billboardParticleRenderer(),
		m_meshParticleRenderer(),
		m_particlePathRenderer(),
		m_bloomEnabled(true),
		m_flareEnabled(true)
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
		return m_toneMapping.getOutputTexture();
	}

	Bloom& ParticleRenderer::getBloom()
	{
		return m_bloom;
	}

	BrightPass& ParticleRenderer::getBrightPass()
	{
		return m_brightPass;
	}

	Flare& ParticleRenderer::getFlare()
	{
		return m_flare;
	}

	HdrComposite& ParticleRenderer::getHdrComposite()
	{
		return m_hdrComposite;
	}

	ToneMapping& ParticleRenderer::getToneMapping()
	{
		return m_toneMapping;
	}

	void ParticleRenderer::setBloomEnabled(bool enabled)
	{
		m_bloomEnabled = enabled;
	}

	void ParticleRenderer::setFlareEnabled(bool enabled)
	{
		m_flareEnabled = enabled;
	}

	bool ParticleRenderer::loadBillboardRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height)
	{
		return m_billboardParticleRenderer.loadTextures(assetRegistry, imageIds, width, height);
	}

	bool ParticleRenderer::loadPathRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height)
	{
		return m_particlePathRenderer.loadTextures(assetRegistry, imageIds, width, height);
	}

	bool ParticleRenderer::loadMeshRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds)
	{
		return m_meshParticleRenderer.loadTextures(assetRegistry, imageIds);
	}

	bool ParticleRenderer::loadMeshRendererMeshes(AssetRegistry& assetRegistry, const std::vector<unsigned int>& modelIds)
	{
		return m_meshParticleRenderer.loadMeshes(assetRegistry, modelIds);
	}

	void ParticleRenderer::resize(unsigned int width, unsigned int height)
	{
		m_width = width;
		m_height = height;

		if (m_width == 0 || m_height == 0)
			return;

		m_framebuffer.resize(width, height);
		m_resolvedFramebuffer.resize(width, height);

		m_bloom.resize(width, height);
		m_brightPass.resize(width, height);
		m_flare.resize(width, height);
		m_hdrComposite.resize(width, height);
		m_toneMapping.resize(width, height);
	}

	void ParticleRenderer::update(const ParticleSimulation& particleSimulation, const AssetRegistry& assetRegistry, const View& view, float elapsedTime)
	{
		m_billboardParticleRenderer.update(particleSimulation.getParticlePools(), particleSimulation.getParticleRegistry(), assetRegistry, elapsedTime);
		m_meshParticleRenderer.update(particleSimulation.getParticlePools(), particleSimulation.getParticleRegistry());
		m_particlePathRenderer.update(particleSimulation.getTrailPools(), particleSimulation.getTrailRegistry(), particleSimulation.getRibbonPools(), particleSimulation.getRibbonRegistry(), view);
	}

	void ParticleRenderer::render(const View& view, const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry, const std::optional<SourceFramebuffer>& sourceFramebuffer) const
	{
		if (m_width == 0 || m_height == 0)
			return;

		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		if (sourceFramebuffer.has_value())
		{
			glBindFramebuffer(GL_FRAMEBUFFER, sourceFramebuffer.value().id);
		}
		else
		{
			m_framebuffer.bind();
			glViewport(0, 0, m_width, m_height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		m_particlePathRenderer.render(view);
		m_billboardParticleRenderer.render(view);
		m_meshParticleRenderer.render(view);
		
		if (sourceFramebuffer.has_value())
		{
			const SourceFramebuffer& sourceFramebufferValue = sourceFramebuffer.value();

			glBindFramebuffer(GL_READ_FRAMEBUFFER, sourceFramebufferValue.id);
			glReadBuffer(GL_COLOR_ATTACHMENT0 + sourceFramebufferValue.colorAttachmentIndex);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_resolvedFramebuffer.getId());
			glDrawBuffer(GL_COLOR_ATTACHMENT0);

			glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_resolvedFramebuffer.getWidth(), m_resolvedFramebuffer.getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);

			glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		}
		else
		{
			m_framebuffer.copy(m_resolvedFramebuffer, GL_COLOR_BUFFER_BIT, 0, 0);
		}

		unsigned int hdrSceneTexture = std::get<Texture>(m_resolvedFramebuffer.getColorAttachment(0)).getId();

		glDisable(GL_BLEND);
		
		if (m_bloomEnabled)
		{
			m_bloom.render(hdrSceneTexture);
			glViewport(0, 0, m_width, m_height);
		}

		if (m_flareEnabled)
		{
			m_brightPass.render(hdrSceneTexture);
			m_flare.render(m_brightPass.getOutputTexture());
			glViewport(0, 0, m_width, m_height);
		}

		m_hdrComposite.render(hdrSceneTexture, m_bloom.getOutputTexture(), m_flare.getOutputTexture());
		m_toneMapping.render(m_hdrComposite.getOutputTexture());
	}

	bool ParticleRenderer::initialize(void* (*loader)(const char*))
	{
		if (m_initialized)
			return true;

		if (gladLoadGLLoader(loader))
			m_initialized = true;

		return m_initialized;
	}
}