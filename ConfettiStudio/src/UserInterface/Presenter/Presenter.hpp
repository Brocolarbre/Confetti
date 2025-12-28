#pragma once

#include "UserInterface/Command/CommandHistory.hpp"

#include <functional>
#include <string>
#include <unordered_map>

class Presenter
{
private:
	std::unordered_map<std::string, std::function<void()>> m_modelEventCallbacks;
	std::unordered_map<std::string, std::function<void()>> m_widgetEventCallbacks;

protected:
	CommandHistory& m_commandHistory;

public:
	Presenter(CommandHistory& commandHistory);

	void registerModelEvent(const std::string& event, const std::function<void()>& callback);
	void registerWidgetEvent(const std::string& event, const std::function<void()>& callback);
	void unregisterModelEvent(const std::string& event);
	void unregisterWidgetEvent(const std::string& event);

	void onModelEvent(const std::string& event);
	void onWidgetEvent(const std::string& event);
};