#pragma once

#include "TrailMesh.hpp"
#include "Confetti/ParticleSimulation/AssetRegistry.hpp"
#include "Confetti/ParticleSimulation/TrailPool.hpp"
#include "Confetti/ParticleSimulation/TrailRegistry.hpp"
#include "Confetti/Renderer/Tools/Shader.hpp"
#include "Confetti/Renderer/Tools/TextureArray.hpp"
#include "Confetti/Renderer/View.hpp"

namespace cft
{
	class TrailRenderer
	{
	private:
		std::unordered_map<unsigned int, unsigned int> m_imageIdToTextureIndex;

		TextureArray m_textureArray;
		TrailMesh m_trailMesh;
		Shader m_shader;

	public:
		TrailRenderer();

		void loadTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height);

		void update(const std::unordered_map<unsigned int, TrailPool>& trailPools, const TrailRegistry& trailRegistry, const View& view);
		void render(const View& view) const;
	};
}