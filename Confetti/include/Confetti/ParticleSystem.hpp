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

	public:
		ParticleSystem(float timeStep, unsigned int maximumStepsPerFrame, unsigned int width, unsigned int height, unsigned int samples, unsigned int mipCount = 5);

		AssetRegistry& getAssetRegistry();
		ParticleSimulation& getParticleSimulation();
		ParticleRenderer& getParticleRenderer();

		unsigned int getRendererOutputTextureId() const;

		void resize(unsigned int width, unsigned int height);
		void clear();

		void setTimeScale(float timeScale);
		void playEffect(unsigned int id, float delay = 0.0f);

		void update(float deltaTime, const View& view);
		void render(const View& view, const std::optional<ParticleRenderer::SourceFramebuffer>& sourceFramebuffer) const;
	};
}