#pragma once

#include "Camera/OrbitCameraController.hpp"

#include <ConfettiEngine/ParticleSimulation.hpp>

class ConfettiInstance
{
private:
	Camera m_camera;
	OrbitCameraController m_cameraController;
	cft::ParticleSimulation m_particleSimulation;

public:
	ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window);

	cft::Renderer& getRenderer();

	void update();
	void render();
};