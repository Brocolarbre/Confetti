#pragma once

#include "ConfettiInstance.hpp"

class Application
{
private:
	dove::Window m_window;
	krono::Chronometer m_chronometer;
	std::unique_ptr<ConfettiInstance> m_confettiInstance;
	
	void update(double deltaTime);
	void render();

public:
	Application();

	void run();
};