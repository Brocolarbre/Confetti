#include "ViewportWidget.hpp"

#include <imgui.h>

ViewportWidget::ViewportWidget() :
	WindowWidget("Viewport", false)
{

}

void ViewportWidget::render()
{
	glm::vec2 size = getSize();
	ImGui::Image(m_texture, ImVec2(size.x, size.y), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
}