#pragma once

#include "UserInterface.hpp"

#include "UserInterface/Model/ConfettiInstance.hpp"

class UserInterfaceBuilder
{
public:
	static void build(UserInterface& userInterface, dove::Window& window, ConfettiInstance& confettiInstance);
};