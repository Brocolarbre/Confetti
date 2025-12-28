#include "UserInterface.hpp"
#include "UserInterfaceStyle.hpp"
#include "OpenGLUserInterfaceBackend.hpp"

#include <Windove/Input/Monitor.hpp>

void UserInterface::renderWidget(std::shared_ptr<Widget> widget)
{
    if (!widget->isEnabled())
        return;

    widget->beginStyle();

    if (widget->beginRender())
    {
        widget->update();
        widget->render();

        for (const std::shared_ptr<Widget>& childWidget : widget->getChildWidgets())
            renderWidget(childWidget);

        widget->endRender();
    }
    else if (widget->alwaysEndRender())
    {
        widget->endRender();
    }

    widget->endStyle();
}

UserInterface::UserInterface(const dove::Window& window) :
    m_rootWidget(),
    m_backend(std::make_unique<OpenGLUserInterfaceBackend>(*reinterpret_cast<GLFWwindow*>(window.getPlatformWindow()), "#version 460 core")),
    m_commandHistory(),
    m_keyboardInputAvailable(true),
    m_mouseInputAvailable(true)
{
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGui::GetIO().IniFilename = nullptr;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;

    m_backend->initialize();
}

UserInterface::~UserInterface()
{
    m_backend->terminate();

    ImGui::DestroyContext();
}

CommandHistory& UserInterface::getCommandHistory()
{
    return m_commandHistory;
}

bool UserInterface::isKeyboardInputAvailable() const
{
    return m_keyboardInputAvailable;
}

bool UserInterface::isMouseInputAvailable() const
{
    return m_mouseInputAvailable;
}

void UserInterface::loadSettings(const std::string& path) const
{
    ImGui::LoadIniSettingsFromDisk(path.c_str());
}

void UserInterface::saveSettings(const std::string& path) const
{
    ImGui::SaveIniSettingsToDisk(path.c_str());
}

void UserInterface::setFont(const std::string& path, unsigned int size)
{
    if (!path.empty() && size > 0)
    {
        ImFontConfig fontConfiguration;
        dove::Vector2f contentScale = dove::Monitor::getContentScale(dove::Monitor::getPrimaryMonitor());
        fontConfiguration.RasterizerDensity = std::max(contentScale.x, contentScale.y);
        ImGui::GetIO().Fonts->AddFontFromFileTTF(path.c_str(), static_cast<float>(size), &fontConfiguration);
    }
}

void UserInterface::setStyle(Theme theme) const
{
    UserInterfaceStyle::apply(ImGui::GetStyle(), theme);
}

void UserInterface::setContext() const
{
    ImGui::SetCurrentContext(ImGui::GetCurrentContext());

    ImGuiMemAllocFunc allocationFunction = nullptr;
    ImGuiMemFreeFunc freeFunction = nullptr;
    void* userData = nullptr;

    ImGui::GetAllocatorFunctions(&allocationFunction, &freeFunction, &userData);
    ImGui::SetAllocatorFunctions(allocationFunction, freeFunction, userData);
}

void UserInterface::setRootWidget(std::shared_ptr<Widget> widget)
{
    m_rootWidget = widget;
}

void UserInterface::render()
{
    m_keyboardInputAvailable = !ImGui::GetIO().WantCaptureKeyboard;
    m_mouseInputAvailable = !ImGui::GetIO().WantCaptureMouse;

    m_backend->beginRender();
    ImGui::NewFrame();

    if(m_rootWidget != nullptr)
        renderWidget(m_rootWidget);

    ImGui::Render();
    m_backend->endRender();
}