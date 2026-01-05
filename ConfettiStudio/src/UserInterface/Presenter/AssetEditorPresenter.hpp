#pragma once

#include "UserInterface/Widget/AssetEditorWidget.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class AssetEditorPresenter : public Presenter
{
private:
	AssetEditorWidget& m_widget;
	ConfettiInstance& m_confettiInstance;

	void onSpawnRateUpdated();
	void onMinimumLifetimeUpdated();
	void onMaximumLifetimeUpdated();
	void onMinimumPositionUpdated();
	void onMaximumPositionUpdated();
	void onMinimumVelocityUpdated();
	void onMaximumVelocityUpdated();
	void onMinimumScaleUpdated();
	void onMaximumScaleUpdated();
	void onMinimumColorUpdated();
	void onMaximumColorUpdated();

public:
	AssetEditorPresenter(CommandHistory& commandHistory, AssetEditorWidget& widget, ConfettiInstance& confettiInstance);
};