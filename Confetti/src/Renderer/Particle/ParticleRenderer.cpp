#include "Confetti/Renderer/Particle/ParticleRenderer.hpp"
#include "Confetti/Renderer/ShaderSource/ParticleShaderSource.hpp"

#include <glad/glad.h>
#include <iostream>

namespace cft
{
	ParticleRenderer::ParticleRenderer(unsigned int width, unsigned int height) :
		m_width(width),
		m_height(height),
		m_imageTextureIdMapping(),
		m_spriteSheetSpriteSheetIdMapping(),
		m_textureArray(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE),
		m_framebuffer(width, height),
		m_resolvedFramebuffer(width, height),
		m_shader(),
		m_mesh(),
		m_particleSsbo(),
		m_spriteSheetSsbo(),
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

		m_shader.loadFromMemory(std::string(PARTICLE_VERTEX_SHADER_SOURCE), std::string(PARTICLE_FRAGMENT_SHADER_SOURCE));
		m_shader.use();
		m_shader.setUniform("uTexture", 0);
	}

	unsigned int ParticleRenderer::getOutputTextureId() const
	{
		return m_toneMapping.getOutputTexture();
	}

	void ParticleRenderer::loadTextures(AssetRegistry& assetRegistry, unsigned int width, unsigned int height)
	{
		m_imageTextureIdMapping.clear();
		const std::unordered_map<unsigned int, Image>& images = assetRegistry.getImages();

		std::vector<std::vector<std::byte>> imageData;
		imageData.reserve(images.size());

		for (const auto& [id, image] : images)
		{
			m_imageTextureIdMapping[id] = static_cast<unsigned int>(imageData.size());
			imageData.push_back(image.getData());

			unsigned int imageWidth = image.getWidth();
			unsigned int imageHeight = image.getHeight();
			
			if (imageWidth != width || imageHeight != height)
				std::cerr << "Particle renderer texture loading error : size mismatch for image at id " << id << " : " << imageWidth << "x" << imageHeight << " instead of " << width << "x" << height << std::endl;
		}

		std::vector<const void*> textureData;
		textureData.reserve(imageData.size());

		for (const std::vector<std::byte>& data : imageData)
			textureData.push_back(data.data());

		m_textureArray.load(textureData, width, height, GL_NEAREST, GL_CLAMP_TO_EDGE);
	}

	void ParticleRenderer::loadSpriteSheets(AssetRegistry& assetRegistry)
	{
		m_spriteSheetSpriteSheetIdMapping.clear();
		const std::unordered_map<unsigned int, SpriteSheet>& spriteSheets = assetRegistry.getSpriteSheets();

		unsigned int spriteSheetCounter = 0;
		std::vector<std::reference_wrapper<const SpriteSheet>> spriteSheetData;
		spriteSheetData.reserve(spriteSheets.size());

		for (const std::pair<unsigned int, SpriteSheet>& spriteSheet : spriteSheets)
		{
			m_spriteSheetSpriteSheetIdMapping[spriteSheet.first] = spriteSheetCounter++;
			spriteSheetData.push_back(std::ref(spriteSheet.second));
		}

		m_spriteSheetSsbo.bind();
		m_spriteSheetSsbo.setData(spriteSheetData);
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

	void ParticleRenderer::render(const View& view, float elapsedTime, const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry)
	{		
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_particleSsbo.setData(particlePools, m_imageTextureIdMapping, m_spriteSheetSpriteSheetIdMapping, particleRegistry, assetRegistry);
		
		m_framebuffer.bind();
		glViewport(0, 0, m_width, m_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_particleSsbo.bind();
		m_spriteSheetSsbo.bind();

		TextureArray::setActiveSlot(0);
		m_textureArray.bind();

		m_shader.use();
		m_shader.setUniform("uView", view.viewMatrix);
		m_shader.setUniform("uProjection", view.projectionMatrix);
		m_shader.setUniform("uTime", elapsedTime);

		m_mesh.drawInstanced(m_particleSsbo.getParticleCount());
		
		m_framebuffer.copy(m_resolvedFramebuffer, GL_COLOR_BUFFER_BIT, 0, 0);

		m_bloom.render(std::get<Texture>(m_resolvedFramebuffer.getColorAttachment(0)).getId(), 0.005f);
		m_toneMapping.render(m_bloom.getBloomTexture().getId());
	}
}