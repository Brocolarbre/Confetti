#pragma once

#include "ParticlePathMesh.hpp"
#include "Confetti/Rendering/Tool/Shader.hpp"
#include "Confetti/Rendering/Tool/TextureArray.hpp"
#include "Confetti/Rendering/View.hpp"
#include "Confetti/Simulation/Pool/RibbonPool.hpp"
#include "Confetti/Simulation/Pool/TrailPool.hpp"
#include "Confetti/Simulation/Registry/AssetRegistry.hpp"
#include "Confetti/Simulation/Registry/RibbonRegistry.hpp"
#include "Confetti/Simulation/Registry/TrailRegistry.hpp"

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

		void generateGeometry(const std::deque<PathPoint>& trail, const PathConfiguration& pathConfiguration, const View& view, ParticlePathGeometry& geometry) const;
		ParticlePathGeometry generateTrailGeometry(const std::unordered_map<unsigned int, TrailPool>& trailPools, const TrailRegistry& trailRegistry, const View& view);
		ParticlePathGeometry generateRibbonGeometry(const std::unordered_map<unsigned int, RibbonPool>& ribbonPools, const RibbonRegistry& ribbonRegistry, const View& view);

	public:
		ParticlePathRenderer();

		void loadTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& imageIds, unsigned int width, unsigned int height);

		void update(const std::unordered_map<unsigned int, TrailPool>& trailPools, const TrailRegistry& trailRegistry, const std::unordered_map<unsigned int, RibbonPool>& ribbonPools, const RibbonRegistry& ribbonRegistry, const View& view);
		void render(const View& view) const;
	};
}