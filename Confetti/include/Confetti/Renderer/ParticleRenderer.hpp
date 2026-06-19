#pragma once

#include "Billboard/BillboardParticleRenderer.hpp"
#include "Mesh/MeshParticleRenderer.hpp"
#include "Confetti/Renderer/PostProcessing/Bloom.hpp"
#include "Confetti/Renderer/PostProcessing/ToneMapping.hpp"
#include "Confetti/Renderer/Tools/Framebuffer.hpp"

namespace cft
{
	class ParticleRenderer
	{
	private:
		unsigned int m_width;
		unsigned int m_height;

		Framebuffer m_framebuffer;
		Framebuffer m_resolvedFramebuffer;
		
		Bloom m_bloom;
		ToneMapping m_toneMapping;

		BillboardParticleRenderer m_billboardParticleRenderer;
		MeshParticleRenderer m_meshParticleRenderer;

	public:
		ParticleRenderer(unsigned int width, unsigned int height);

		unsigned int getOutputTextureId() const;

		void loadBillboardRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& images, unsigned int width, unsigned int height);
		void loadMeshRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& images);
		void loadMeshRendererMeshes(AssetRegistry& assetRegistry, const std::vector<unsigned int>& models);

		void resize(unsigned int width, unsigned int height);
		void update(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry);
		void render(const View& view, float elapsedTime, const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry);
	};
}