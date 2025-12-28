#include "CameraController.hpp"

CameraController::CameraController(Camera& camera, dove::Window& window) :
	m_camera(camera),
	m_window(window)
{
	m_window.addEventHandler(*this);
}

CameraController::~CameraController()
{
	m_window.removeEventHandler(*this);
}