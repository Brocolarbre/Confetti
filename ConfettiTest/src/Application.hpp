#pragma once

#include "ConfettiInstance.hpp"

class Application
{
private:
	dove::Window m_window;
	std::unique_ptr<ConfettiInstance> m_confettiInstance;
	
	void update();
	void render();

public:
	Application();
	~Application();

	void run();
};