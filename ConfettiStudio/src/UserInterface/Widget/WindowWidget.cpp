#include "WindowWidget.hpp"

#include <imgui.h>

bool WindowWidget::isHovered() const
{
	return ImGui::IsWindowHovered();
}

WindowWidget::WindowWidget(const std::string& name, bool child) :
	Widget(name, true),
	m_child(child)
{

}

bool WindowWidget::beginRender() const
{
	if (m_child)
		return ImGui::BeginChild(m_name.c_str());
	else
		return ImGui::Begin(m_name.c_str());
}

void WindowWidget::endRender() const
{
	if (m_child)
		ImGui::EndChild();
	else
		ImGui::End();
}