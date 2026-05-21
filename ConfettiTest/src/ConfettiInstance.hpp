#pragma once

#include <Confetti/Particle/ParticleSimulation.hpp>
#include <Confetti/Renderer/Renderer.hpp>
#include <Krono/Krono.hpp>
#include <Windove/Window.hpp>

class ConfettiInstance : public dove::EventHandler
{
private:
	cft::ParticleSimulation m_particleSimulation;
	cft::Renderer m_renderer;
	krono::Chronometer m_elapsedTimeChronometer;
	krono::Chronometer m_deltaTimeChronometer;

	void restartSimulation();

public:
	ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window);

	void onKeyPressed(dove::KeyEvent keyEvent) override;

	void update();
	void render();
};