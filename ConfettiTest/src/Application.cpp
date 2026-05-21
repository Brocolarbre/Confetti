#include "Application.hpp"

void Application::update(double deltaTime)
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
	m_window("Confetti Studio", 1280, 720, dove::WindowSettings{ .openGLVersionMajor = 4, .openGLVersionMinor = 6 }),
	m_chronometer(),
	m_confettiInstance()
{
	m_window.captureContext();
	cft::Renderer::initialize(dove::Window::getProcAddress);

	dove::Vector2 windowSize = m_window.getSize();
	m_confettiInstance = std::make_unique<ConfettiInstance>(windowSize.x, windowSize.y, m_window);
	UserInterfaceBuilder::build(m_userInterface, m_window, *m_confettiInstance);
}

void Application::run()
{
	while (m_window.isOpen())
	{
		double deltaTime = m_chronometer.getElapsedTime().seconds;
		m_chronometer.restart();

		update(deltaTime);
		render();
	}
}