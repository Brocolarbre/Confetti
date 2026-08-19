#pragma once

#include "BillboardParticleMesh.hpp"
#include "BillboardParticleSsbo.hpp"
#include "Confetti/Rendering/Tool/Shader.hpp"
#include "Confetti/Rendering/Tool/TextureArray.hpp"
#include "Confetti/Rendering/View.hpp"
#include "SpriteSheetSSBO.hpp"

namespace cft
{
	class CONFETTI_API BillboardParticleRenderer
	{
	private:
		std::unordered_map<unsigned int, unsigned int> m_imageIdToTextureIndex;
		std::unordered_map<unsigned int, unsigned int> m_spriteSheetIdToSpriteSheetSsboIndexMapping;
		TextureArray m_textureArray;
		SpriteSheetSSBO m_spriteSheetSsbo;
		BillboardParticleSSBO m_particleSsbo;
		Shader m_shader;
		BillboardParticleMesh m_mesh;
		float m_elapsedTime;

		void loadSpriteSheets(AssetRegistry& assetRegistry);

	public:
		BillboardParticleRenderer();

		bool loadTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height);

		void update(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry, float elapsedTime);
		void render(const View& view) const;
	};
}