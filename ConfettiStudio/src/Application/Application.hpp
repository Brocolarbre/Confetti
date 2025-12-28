#pragma once

#include "UserInterface/Core/UserInterface.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

#include <Windove/Window.hpp>
#include <Krono/Krono.hpp>

class Application
{
private:
	dove::Window m_window;
	krono::Chronometer m_chronometer;
	double m_timeStep;
	double m_accumulator;

	UserInterface m_userInterface;
	ConfettiInstance m_confettiInstance;

	void fixedUpdate(double fixedTimeStep);
	void update(double deltaTime);
	void render();

public:
	Application();
	~Application();

	void run();
};