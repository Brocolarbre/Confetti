#pragma once

#include "UserInterface/Widget/ViewportWidget.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class ViewportPresenter : public Presenter
{
private:
	ViewportWidget& m_widget;
	ConfettiInstance& m_confettiInstance;

	void onResized();

public:
	ViewportPresenter(CommandHistory& commandHistory, ViewportWidget& widget, ConfettiInstance& confettiInstance);
};