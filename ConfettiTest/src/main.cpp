#pragma once

#include "Application/Application.hpp"

int main()
{
	dove::Window::initialize();

	Application application;
	application.run();

	dove::Window::terminate();

	return 0;
}