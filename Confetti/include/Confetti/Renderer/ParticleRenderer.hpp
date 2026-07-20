
#include "Billboard/BillboardParticleRenderer.hpp"
#include "Mesh/MeshParticleRenderer.hpp"
#include "ParticlePath/ParticlePathRenderer.hpp"
#include "Confetti/Renderer/PostProcessing/Bloom.hpp"
#include "Confetti/Renderer/PostProcessing/BrightPass.hpp"
#include "Confetti/Renderer/PostProcessing/Flare.hpp"
#include "Confetti/Renderer/PostProcessing/HdrComposite.hpp"
#include "Confetti/Renderer/PostProcessing/ToneMapping.hpp"
#include "Confetti/Renderer/Tools/Framebuffer.hpp"
#include "Confetti/ParticleSimulation/ParticleSimulation.hpp"

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
		BrightPass m_brightPass;
		Flare m_flare;
		HdrComposite m_hdrComposite;
		ToneMapping m_toneMapping;

		BillboardParticleRenderer m_billboardParticleRenderer;
		MeshParticleRenderer m_meshParticleRenderer;
		ParticlePathRenderer m_particlePathRenderer;

	public:
		ParticleRenderer(unsigned int width, unsigned int height, unsigned int samples);

		unsigned int getOutputTextureId() const;

		void loadBillboardRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height);
		void loadMeshRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds);
		void loadMeshRendererMeshes(AssetRegistry& assetRegistry, const std::vector<unsigned int>& modelIds);
		void loadTrailRendererTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height);

		void resize(unsigned int width, unsigned int height);
		void update(const ParticleSimulation& particleSimulation, const AssetRegistry& assetRegistry, const View& view);
		void render(const View& view, float elapsedTime, const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry, const AssetRegistry& assetRegistry);
	};
}