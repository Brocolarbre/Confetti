#pragma once

#include "Confetti/ParticleSimulation/AssetRegistry.hpp"
#include "Confetti/Renderer/Particle/ParticleMesh.hpp"
#include "Confetti/Renderer/Particle/ParticleSSBO.hpp"
#include "Confetti/Renderer/Particle/View.hpp"
#include "Confetti/Renderer/Tools/Framebuffer.hpp"
#include "Confetti/Renderer/Tools/Shader.hpp"
#include "Confetti/Renderer/Tools/TextureArray.hpp"
#include "Confetti/Renderer/PostProcessing/Bloom.hpp"
#include "Confetti/Renderer/PostProcessing/ToneMapping.hpp"

namespace cft
{
	class ParticleRenderer
	{
	private:
		unsigned int m_width;
		unsigned int m_height;

		std::unordered_map<unsigned int, unsigned int> m_imageTextureIdMapping;

		TextureArray m_textureArray;
		Framebuffer m_framebuffer;
		Framebuffer m_resolvedFramebuffer;
		Shader m_shader;
		ParticleMesh m_mesh;
		SSBO m_ssbo;

		Bloom m_bloom;
		ToneMapping m_toneMapping;

	public:
		ParticleRenderer(unsigned int width, unsigned int height);

		unsigned int getOutputTextureId() const;

		void loadTextures(AssetRegistry& assetRegistry, unsigned int width, unsigned int height);
		void resize(unsigned int width, unsigned int height);
		void render(const View& view, const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry);
	};
}