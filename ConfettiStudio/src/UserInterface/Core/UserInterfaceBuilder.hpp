#pragma once

#include "UserInterface.hpp"

class UserInterfaceBuilder
{
public:
	static void build(UserInterface& userInterface, dove::Window& window);
};