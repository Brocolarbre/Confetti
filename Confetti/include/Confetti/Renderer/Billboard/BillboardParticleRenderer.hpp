#pragma once

#include "BillboardParticleMesh.hpp"
#include "BillboardParticleSsbo.hpp"
#include "Confetti/Renderer/Tools/Shader.hpp"
#include "Confetti/Renderer/Tools/TextureArray.hpp"
#include "Confetti/Renderer/View.hpp"
#include "SpriteSheetSSBO.hpp"

namespace cft
{
	class BillboardParticleRenderer
	{
	private:
		std::unordered_map<unsigned int, unsigned int> m_imageIdToTextureId;
		std::unordered_map<unsigned int, unsigned int> m_spriteSheetIdToSpriteSheetSsboIdMapping;
		TextureArray m_textureArray;
		SpriteSheetSSBO m_spriteSheetSsbo;
		BillboardParticleSSBO m_particleSsbo;
		Shader m_shader;
		BillboardParticleMesh m_mesh;

		void loadSpriteSheets(AssetRegistry& assetRegistry);

	public:
		BillboardParticleRenderer();

		void loadTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& images, unsigned int width, unsigned int height);

		void update(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry);
		void render(const View& view, float elapsedTime) const;
	};
}