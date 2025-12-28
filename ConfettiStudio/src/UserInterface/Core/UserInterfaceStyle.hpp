#pragma once

#include "UserInterface.hpp"

struct ImGuiStyle;

class UserInterfaceStyle
{
public:
	static void apply(ImGuiStyle& style, UserInterface::Theme theme);
};