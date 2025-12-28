#include "Presenter.hpp"

Presenter::Presenter(CommandHistory& commandHistory) :
	m_modelEventCallbacks(),
	m_widgetEventCallbacks(),
	m_commandHistory(commandHistory)
{

}

void Presenter::registerModelEvent(const std::string& event, const std::function<void()>& callback)
{
	m_modelEventCallbacks[event] = callback;
}

void Presenter::registerWidgetEvent(const std::string& event, const std::function<void()>& callback)
{
	m_widgetEventCallbacks[event] = callback;
}

void Presenter::unregisterModelEvent(const std::string& event)
{
	m_modelEventCallbacks.erase(event);
}

void Presenter::unregisterWidgetEvent(const std::string& event)
{
	m_widgetEventCallbacks.erase(event);
}

void Presenter::onModelEvent(const std::string& event)
{
	if (m_modelEventCallbacks.contains(event))
		m_modelEventCallbacks.at(event)();
}

void Presenter::onWidgetEvent(const std::string& event)
{
	if (m_widgetEventCallbacks.contains(event))
		m_widgetEventCallbacks.at(event)();
}