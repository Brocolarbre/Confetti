#pragma once

#include "RenderContext.hpp"

#include <Confetti/ParticleSimulation/ParticleSimulation.hpp>
#include <Confetti/Renderer/Particle/ParticleRenderer.hpp>
#include <Krono/Krono.hpp>
#include <Windove/Window.hpp>

class ConfettiInstance : public dove::EventHandler
{
private:
	RenderContext m_renderContext;

	cft::AssetRegistry m_assetRegistry;
	cft::RandomNumberGenerator m_randomNumberGenerator;
	cft::ParticleRenderer m_particleRenderer;
	cft::ParticleSimulation m_particleSimulation;

	krono::Chronometer m_elapsedTimeChronometer;
	krono::Chronometer m_deltaTimeChronometer;
	double m_timeStep;
	double m_timeAccumulator;
	double m_elapsedTime;

	unsigned int m_width;
	unsigned int m_height;

	void restartSimulation();
	void updateSimulation(float elapsedTime, float deltaTime);

public:
	ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window);

	void onKeyPressed(dove::KeyEvent keyEvent) override;
	void onWindowResized(unsigned int width, unsigned int height) override;

	void update();
	void render();
};