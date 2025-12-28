#pragma once

#include "UserInterfaceBackend.hpp"

#include <string>
#include <imgui_impl_glfw.h>

class OpenGLUserInterfaceBackend : public UserInterfaceBackend
{
private:
	GLFWwindow& m_window;
	std::string m_glslVersion;

public:
	OpenGLUserInterfaceBackend(GLFWwindow& window, const std::string& glslVersion);

	void initialize() const override;
	void terminate() const override;
	void beginRender() const override;
	void endRender() const override;
};