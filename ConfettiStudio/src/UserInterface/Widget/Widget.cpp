#include "Widget.hpp"

#include <imgui.h>

Widget::Widget(const std::string& name, bool alwaysEndRender) :
	m_name(name),
	m_alwaysEndRender(alwaysEndRender),
	m_enabled(true),
	m_childWidgets(),
	m_presenter(),
	m_position(0.0f, 0.0f),
	m_size(0.0f, 0.0f),
	m_hovered(false)
{

}

std::string Widget::getName() const
{
	return m_name;
}

bool Widget::alwaysEndRender() const
{
	return m_alwaysEndRender;
}

bool Widget::isEnabled() const
{
	return m_enabled;
}

const std::vector<std::shared_ptr<Widget>>& Widget::getChildWidgets() const
{
	return m_childWidgets;
}

void Widget::addChildWidget(std::shared_ptr<Widget> widget)
{
	m_childWidgets.push_back(widget);
}

void Widget::removeChildWidget(const std::string& name)
{
	std::vector<std::shared_ptr<Widget>>::iterator widget = std::find_if(m_childWidgets.begin(), m_childWidgets.end(), [&name](std::shared_ptr<Widget> widget) { return widget->getName() == name; });

	if (widget != m_childWidgets.end())
		m_childWidgets.erase(widget);
}

void Widget::setEnabled(bool enabled)
{
	m_enabled = enabled;
}

glm::vec2 Widget::getPosition() const
{
	return m_position;
}

glm::vec2 Widget::getSize() const
{
	return m_size;
}

void Widget::registerPresenter(std::shared_ptr<Presenter> presenter)
{
	m_presenter = presenter;
}

void Widget::unregisterPresenter()
{
	m_presenter.reset();
}

void Widget::sendEvent(const std::string& event) const
{
	if (m_presenter)
		m_presenter->onWidgetEvent(event);
}

void Widget::beginStyle() const
{

}

void Widget::update()
{
	if (isHovered())
	{
		if (!m_hovered)
		{
			m_hovered = true;
			sendEvent("hovered");
		}
	}
	else
	{
		if (m_hovered)
		{
			m_hovered = false;
			sendEvent("unhovered");
		}
	}

	ImVec2 position = ImGui::GetCursorScreenPos();
	if (position.x != m_position.x || position.y != m_position.y)
	{
		m_position = glm::vec2(position.x, position.y);
		sendEvent("moved");
	}

	ImVec2 size = ImGui::GetContentRegionAvail();
	if (size.x != m_size.x || size.y != m_size.y)
	{
		m_size = glm::max(glm::vec2(size.x, size.y), glm::vec2(0.0f));
		sendEvent("resized");
	}
}

void Widget::endStyle() const
{

}