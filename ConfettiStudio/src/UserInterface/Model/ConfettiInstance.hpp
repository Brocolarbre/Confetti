#pragma once

#include "Camera/OrbitCameraController.hpp"

#include <ConfettiEngine/Particle/ParticleSimulation.hpp>
#include <ConfettiEngine/Renderer/Renderer.hpp>
#include <Krono/Krono.hpp>

class ConfettiInstance
{
private:
	Camera m_camera;
	OrbitCameraController m_cameraController;
	cft::ParticleSimulation m_particleSimulation;
	cft::Renderer m_renderer;
	krono::Chronometer m_elapsedTimeChronometer;
	krono::Chronometer m_deltaTimeChronometer;

	void restartSimulation();

public:
	ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window);

	cft::Renderer& getRenderer();

	void update();
	void render();
};