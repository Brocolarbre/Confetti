#pragma once

#include "Camera/OrbitCameraController.hpp"

#include <ConfettiEngine/Renderer/Renderer.hpp>

class ConfettiInstance
{
private:
	cft::Renderer m_renderer;
	Camera m_camera;
	OrbitCameraController m_cameraController;

public:
	ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window);

	cft::Renderer& getRenderer();

	void update();
	void render();
};