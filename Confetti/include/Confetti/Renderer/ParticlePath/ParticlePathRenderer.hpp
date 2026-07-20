#pragma once

#include "ParticlePathMesh.hpp"
#include "Confetti/ParticleSimulation/AssetRegistry.hpp"
#include "Confetti/ParticleSimulation/RibbonPool.hpp"
#include "Confetti/ParticleSimulation/RibbonRegistry.hpp"
#include "Confetti/ParticleSimulation/TrailPool.hpp"
#include "Confetti/ParticleSimulation/TrailRegistry.hpp"
#include "Confetti/Renderer/Tools/Shader.hpp"
#include "Confetti/Renderer/Tools/TextureArray.hpp"
#include "Confetti/Renderer/View.hpp"

namespace cft
{
	class ParticlePathRenderer
	{
	private:
		struct ParticlePathGeometry
		{
			std::vector<ParticlePathMesh::Vertex> vertexData;
			std::vector<int> first;
			std::vector<int> count;
		};

	private:
		std::unordered_map<unsigned int, unsigned int> m_imageIdToTextureIndex;

		TextureArray m_textureArray;
		ParticlePathMesh m_trailMesh;
		Shader m_shader;

		void generateGeometry(const std::deque<TrailPoint>& trail, const PathConfiguration& pathConfiguration, const View& view, ParticlePathGeometry& geometry) const;
		ParticlePathGeometry generateTrailGeometry(const std::unordered_map<unsigned int, TrailPool>& trailPools, const TrailRegistry& trailRegistry, const View& view);
		ParticlePathGeometry generateRibbonGeometry(const std::unordered_map<unsigned int, RibbonPool>& ribbonPools, const RibbonRegistry& ribbonRegistry, const View& view);

	public:
		ParticlePathRenderer();

		void loadTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height);

		void update(const std::unordered_map<unsigned int, TrailPool>& trailPools, const TrailRegistry& trailRegistry, const std::unordered_map<unsigned int, RibbonPool>& ribbonPools, const RibbonRegistry& ribbonRegistry, const View& view);
		void render(const View& view) const;
	};
}