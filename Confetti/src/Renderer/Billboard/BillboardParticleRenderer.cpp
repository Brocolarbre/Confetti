#include "Confetti/Renderer/Billboard/BillboardParticleRenderer.hpp"
#include "Confetti/Renderer/ShaderSource/BillboardParticleShaderSource.hpp"

#include <glad/glad.h>
#include <iostream>

namespace cft
{
	void BillboardParticleRenderer::loadSpriteSheets(AssetRegistry& assetRegistry)
	{
		m_spriteSheetIdToSpriteSheetSsboIdMapping.clear();
		const std::unordered_map<unsigned int, SpriteSheet>& spriteSheets = assetRegistry.getSpriteSheets();

		unsigned int spriteSheetCounter = 0;
		std::vector<std::reference_wrapper<const SpriteSheet>> spriteSheetData;
		spriteSheetData.reserve(spriteSheets.size());

		for (const std::pair<unsigned int, SpriteSheet>& spriteSheet : spriteSheets)
		{
			m_spriteSheetIdToSpriteSheetSsboIdMapping[spriteSheet.first] = spriteSheetCounter++;
			spriteSheetData.push_back(std::ref(spriteSheet.second));
		}

		m_spriteSheetSsbo.bind();
		m_spriteSheetSsbo.setData(spriteSheetData);
	}

	BillboardParticleRenderer::BillboardParticleRenderer() :
		m_imageIdToTextureId(),
		m_spriteSheetIdToSpriteSheetSsboIdMapping(),
		m_textureArray(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE),
		m_spriteSheetSsbo(),
		m_particleSsbo(),
		m_shader(),
		m_mesh()
	{
		m_shader.loadFromMemory(std::string(BILLBOARD_PARTICLE_VERTEX_SHADER_SOURCE), std::string(BILLBOARD_PARTICLE_FRAGMENT_SHADER_SOURCE));
		m_shader.use();
		m_shader.setUniform("uTexture", 0);
	}

	void BillboardParticleRenderer::loadTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& images, unsigned int width, unsigned int height)
	{
		m_imageIdToTextureId.clear();

		std::vector<std::vector<std::byte>> imageData;
		imageData.reserve(images.size());

		for (unsigned int imageId : images)
		{
			const Image& image = assetRegistry.getImage(imageId);
			m_imageIdToTextureId[imageId] = static_cast<unsigned int>(imageData.size());
			imageData.push_back(image.getData());

			unsigned int imageWidth = image.getWidth();
			unsigned int imageHeight = image.getHeight();

			if (imageWidth != width || imageHeight != height)
				std::cerr << "Particle renderer texture loading error : size mismatch for image at id " << imageId << " : " << imageWidth << "x" << imageHeight << " instead of " << width << "x" << height << std::endl;
		}

		std::vector<const void*> textureData;
		textureData.reserve(imageData.size());

		for (const std::vector<std::byte>& data : imageData)
			textureData.push_back(data.data());

		m_textureArray.load(textureData, width, height, GL_NEAREST, GL_CLAMP_TO_EDGE);

		loadSpriteSheets(assetRegistry);
	}

	void BillboardParticleRenderer::update(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry)
	{
		m_particleSsbo.bind();
		m_particleSsbo.setData(particlePools, m_imageIdToTextureId, m_spriteSheetIdToSpriteSheetSsboIdMapping, particleRegistry, assetRegistry);
	}

	void BillboardParticleRenderer::render(const View& view, float elapsedTime) const
	{
		TextureArray::setActiveSlot(0);
		m_textureArray.bind();

		m_spriteSheetSsbo.bind();
		m_particleSsbo.bind();

		m_shader.use();
		m_shader.setUniform("uView", view.viewMatrix);
		m_shader.setUniform("uProjection", view.projectionMatrix);
		m_shader.setUniform("uTime", elapsedTime);

		m_mesh.drawInstanced(m_particleSsbo.getParticleCount());
	}
}