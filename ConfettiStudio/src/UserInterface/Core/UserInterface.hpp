#pragma once

#include "UserInterfaceBackend.hpp"
#include "UserInterface/Command/CommandHistory.hpp"
#include "UserInterface/Widget/Widget.hpp"

#include <Windove/Window.hpp>

class UserInterface
{
private:
	std::shared_ptr<Widget> m_rootWidget;
	std::unique_ptr<UserInterfaceBackend> m_backend;
	CommandHistory m_commandHistory;

	bool m_keyboardInputAvailable;
	bool m_mouseInputAvailable;

	void renderWidget(std::shared_ptr<Widget> widget);

public:
	enum class Theme
	{
		Dark = 0,
		Light
	};

	UserInterface(const dove::Window& window);
	~UserInterface();

	CommandHistory& getCommandHistory();

	bool isKeyboardInputAvailable() const;
	bool isMouseInputAvailable() const;

	void loadSettings(const std::string& path) const;
	void saveSettings(const std::string& path) const;

	void setFont(const std::string& path, unsigned int size);
	void setStyle(Theme theme) const;
	void setContext() const;

	void setRootWidget(std::shared_ptr<Widget> widget);

	void render();
};