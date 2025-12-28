#include "Application.hpp"

#include "UserInterface/Core/UserInterfaceBuilder.hpp"

void Application::fixedUpdate(double fixedTimeStep)
{

}

void Application::update(double deltaTime)
{
	m_window.fetchEvents();
}

void Application::render()
{
	m_userInterface.setContext();
	m_userInterface.render();

	m_window.display();
}

Application::Application() :
	m_window("Confetti Studio", 1280, 720, dove::WindowSettings{ .openGLVersionMajor = 4, .openGLVersionMinor = 6 }),
	m_chronometer(),
	m_timeStep(1.0 / 60.0),
	m_accumulator(0.0),
	m_userInterface(m_window),
	m_confettiInstance()
{
	m_window.captureContext();
	cft::Renderer::initialize();

	UserInterfaceBuilder::build(m_userInterface, m_window);
}

Application::~Application()
{
	m_userInterface.saveSettings("res/settings/user_interface.ini");
}

void Application::run()
{
	while (m_window.isOpen())
	{
		double deltaTime = m_chronometer.getElapsedTime().seconds;
		m_chronometer.restart();

		m_accumulator += deltaTime;
		while (m_accumulator >= m_timeStep)
		{
			fixedUpdate(m_timeStep);
			m_accumulator -= deltaTime;
		}

		update(deltaTime);
		render();
	}
}