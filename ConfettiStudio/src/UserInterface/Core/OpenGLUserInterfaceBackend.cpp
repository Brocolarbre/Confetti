#include "OpenGLUserInterfaceBackend.hpp"

#include <imgui.h>
#include <imgui_impl_opengl3.h>

OpenGLUserInterfaceBackend::OpenGLUserInterfaceBackend(GLFWwindow& window, const std::string& glslVersion) :
	m_window(window),
	m_glslVersion(glslVersion)
{

}

void OpenGLUserInterfaceBackend::initialize() const
{
	ImGui_ImplGlfw_InitForOpenGL(&m_window, true);
	ImGui_ImplOpenGL3_Init(m_glslVersion.c_str());
}

void OpenGLUserInterfaceBackend::terminate() const
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
}

void OpenGLUserInterfaceBackend::beginRender() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
}

void OpenGLUserInterfaceBackend::endRender() const
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}