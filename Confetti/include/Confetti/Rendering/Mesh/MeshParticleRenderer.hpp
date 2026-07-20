#pragma once

#include "MeshParticleMesh.hpp"
#include "MeshParticleSsbo.hpp"
#include "Confetti/Simulation/Pool/ParticlePool.hpp"
#include "Confetti/Simulation/Registry/ParticleRegistry.hpp"
#include "Confetti/Rendering/View.hpp"
#include "Confetti/Rendering/Tool/Shader.hpp"
#include "Confetti/Rendering/Tool/Texture.hpp"

namespace cft
{
	class MeshParticleRenderer
	{
	private:
		std::unordered_map<unsigned int, Texture> m_textures;
		std::unordered_map<unsigned int, MeshParticleMesh> m_meshes;
		std::vector<MeshParticleBatch> m_particleBatches;
		MeshParticleSSBO m_particleSsbo;
		Shader m_shader;

	public:
		MeshParticleRenderer();

		void loadTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds);
		void loadMeshes(AssetRegistry& assetRegistry, const std::vector<unsigned int>& modelIds);

		void update(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry);
		void render(const View& view) const;
	};
}