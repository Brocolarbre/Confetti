#pragma once

#include "Camera.hpp"

#include <Windove/Window.hpp>

class CameraController : public dove::EventHandler
{
protected:
	Camera& m_camera;
	dove::Window& m_window;

public:
	CameraController(Camera& camera, dove::Window& window);
	virtual ~CameraController();

	virtual void update() = 0;
};