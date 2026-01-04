#include "ViewportPresenter.hpp"

void ViewportPresenter::onResized()
{
	glm::uvec2 viewportSize = glm::uvec2(glm::max(m_widget.getSize(), glm::vec2(0.0f)));

	m_confettiInstance.getCamera().getViewFrustum().setSize(glm::vec2(viewportSize));
	m_confettiInstance.getCamera().getViewPlane().setSize(glm::vec2(viewportSize));
	m_confettiInstance.getRenderer().resize(viewportSize.x, viewportSize.y);
	m_widget.m_texture = m_confettiInstance.getRenderer().getOutputTextureId();
	m_confettiInstance.render();
}

ViewportPresenter::ViewportPresenter(CommandHistory& commandHistory, ViewportWidget& widget, ConfettiInstance& confettiInstance) :
	Presenter(commandHistory),
	m_widget(widget),
	m_confettiInstance(confettiInstance)
{
	registerWidgetEvent("resized", std::bind(&ViewportPresenter::onResized, this));
}