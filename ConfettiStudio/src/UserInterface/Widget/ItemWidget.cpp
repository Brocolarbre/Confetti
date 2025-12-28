#include "ItemWidget.hpp"

#include <imgui.h>

bool ItemWidget::isHovered() const
{
	return ImGui::IsItemHovered();
}

ItemWidget::ItemWidget(const std::string& name) :
	Widget(name, false)
{

}