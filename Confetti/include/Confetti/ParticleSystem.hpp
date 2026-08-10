#pragma once

#include "Rendering/ParticleRenderer.hpp"

namespace cft
{
	class CONFETTI_API ParticleSystem
	{
	private:
		AssetRegistry m_assetRegistry;
		ParticleSimulation m_simulation;
		ParticleRenderer m_renderer;

		float m_timeStep;
		float m_timeScale;

		float m_elapsedTime;
		float m_timeAccumulator;

		unsigned int m_maximumStepsPerFrame;

		friend class JsonLoader;

	public:
		ParticleSystem(float timeStep, unsigned int maximumStepsPerFrame, unsigned int width, unsigned int height, unsigned int samples);

		AssetRegistry& getAssetRegistry();
		unsigned int getRendererOutputTextureId() const;

		void loadBillboardRendererTextures(const std::vector<unsigned int>& billboardImageIds, unsigned int imageWidth, unsigned int imageHeight);
		void loadMeshRendererTextures(const std::vector<unsigned int>& meshImageIds);
		void loadMeshRendererMeshes(const std::vector<unsigned int>& meshModelIds);

		void resize(unsigned int width, unsigned int height);
		void clear();

		void setTimeScale(float timeScale);
		void playEffect(unsigned int id, float delay = 0.0f);

		void update(float deltaTime, const View& view);
		void render(const View& view) const;
	};
}