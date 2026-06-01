#pragma once

#include "RenderContext.hpp"

#include <Confetti/ParticleSimulation/ParticleSimulation.hpp>
#include <Confetti/Renderer/Renderer.hpp>
#include <Krono/Krono.hpp>
#include <Windove/Window.hpp>

class ConfettiInstance : public dove::EventHandler
{
private:
	RenderContext m_renderContext;

	cft::AssetRegistry m_assetRegistry;
	cft::RandomNumberGenerator m_randomNumberGenerator;
	cft::Renderer m_renderer;
	cft::ParticleSimulation m_particleSimulation;

	krono::Chronometer m_elapsedTimeChronometer;
	krono::Chronometer m_deltaTimeChronometer;

	void restartSimulation();

public:
	ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window);

	void onKeyPressed(dove::KeyEvent keyEvent) override;
	void onWindowResized(unsigned int width, unsigned int height) override;

	void update();
	void render();
};