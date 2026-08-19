#pragma once

#include "Billboard/BillboardParticleRenderer.hpp"
#include "Mesh/MeshParticleRenderer.hpp"
#include "ParticlePath/ParticlePathRenderer.hpp"
#include "Confetti/Rendering/PostProcessing/Bloom.hpp"
#include "Confetti/Rendering/PostProcessing/BrightPass.hpp"
#include "Confetti/Rendering/PostProcessing/Flare.hpp"
#include "Confetti/Rendering/PostProcessing/HdrComposite.hpp"
#include "Confetti/Rendering/PostProcessing/ToneMapping.hpp"
#include "Confetti/Rendering/Tool/Framebuffer.hpp"
#include "Confetti/Simulation/Core/ParticleSimulation.hpp"

namespace cft
{
	class CONFETTI_API ParticleRenderer
	{
	public:
		struct SourceFramebuffer
		{
			unsigned int id;
			unsigned int colorAttachmentIndex;
		};

	private:
		unsigned int m_width;
		unsigned int m_height;

		Framebuffer m_framebuffer;
		Framebuffer m_resolvedFramebuffer;
		
		Bloom m_bloom;
		BrightPass m_brightPass;
		Flare m_flare;
		HdrComposite m_hdrComposite;
		ToneMapping m_toneMapping;

		BillboardParticleRenderer m_billboardParticleRenderer;
		MeshParticleRenderer m_meshParticleRenderer;
		ParticlePathRenderer m_particlePathRenderer;

		bool m_bloomEnabled;
		bool m_flareEnabled;

		static bool m_initialized;

	public:
		ParticleRenderer(unsigned int width, unsigned int height, unsigned int samples, unsigned int mipCount = 5);

		unsigned int getOutputTextureId() const;

		Bloom& getBloom();
		BrightPass& getBrightPass();
		Flare& getFlare();
		HdrComposite& getHdrComposite();
		ToneMapping& getToneMapping();

		void setBloomEnabled(bool enabled);
		void setFlareEnabled(bool enabled);

		bool loadBillboardRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height);
		bool loadPathRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height);
		bool loadMeshRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds);
		bool loadMeshRendererMeshes(AssetRegistry& assetRegistry, const std::vector<unsigned int>& modelIds);

		void resize(unsigned int width, unsigned int height);

		void update(const ParticleSimulation& particleSimulation, const AssetRegistry& assetRegistry, const View& view, float elapsedTime);
		void render(const View& view, const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry, const std::optional<SourceFramebuffer>& sourceFramebuffer) const;

		static bool initialize(void* (*)(const char* loader));
	};
}