#include "Application.hpp"

#include <iostream>

void Application::update()
{
	m_window.fetchEvents();
	m_confettiInstance->update();
}

void Application::render()
{
	m_confettiInstance->render();
	m_window.display();
}

Application::Application() :
	m_window(),
	m_confettiInstance()
{
	dove::Window::initialize();

	dove::WindowSettings windowSettings;
	windowSettings.openGLVersionMajor = 4;
	windowSettings.openGLVersionMinor = 6;

	m_window.open("Confetti", 1280, 720, windowSettings);

	m_window.captureContext();
	if (!RenderContext::initialize(dove::Window::getProcAddress))
		std::cerr << "Failed to initialize render context" << std::endl;

	dove::Vector2 windowSize = m_window.getSize();
	m_confettiInstance = std::make_unique<ConfettiInstance>(windowSize.x, windowSize.y, m_window);
}

Application::~Application()
{
	dove::Window::terminate();
}

void Application::run()
{
	while (m_window.isOpen())
	{
		update();
		render();
	}
}