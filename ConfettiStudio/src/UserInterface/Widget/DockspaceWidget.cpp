#include "DockspaceWidget.hpp"

#include <imgui.h>

bool DockspaceWidget::isHovered() const
{
	return false;
}

DockspaceWidget::DockspaceWidget() :
	Widget("Dockspace", false)
{

}

bool DockspaceWidget::beginRender() const
{
	return true;
}

void DockspaceWidget::render()
{
	ImGui::DockSpaceOverViewport(ImGui::GetID("Dockspace"), ImGui::GetMainViewport());
}

void DockspaceWidget::endRender() const
{

}