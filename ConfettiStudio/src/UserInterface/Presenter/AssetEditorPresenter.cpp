#include "AssetEditorPresenter.hpp"

void AssetEditorPresenter::onSpawnRateUpdated()
{

}

void AssetEditorPresenter::onMinimumLifetimeUpdated()
{

}

void AssetEditorPresenter::onMaximumLifetimeUpdated()
{

}

void AssetEditorPresenter::onMinimumPositionUpdated()
{

}

void AssetEditorPresenter::onMaximumPositionUpdated()
{

}

void AssetEditorPresenter::onMinimumVelocityUpdated()
{

}

void AssetEditorPresenter::onMaximumVelocityUpdated()
{

}

void AssetEditorPresenter::onMinimumScaleUpdated()
{

}

void AssetEditorPresenter::onMaximumScaleUpdated()
{

}

void AssetEditorPresenter::onMinimumColorUpdated()
{

}

void AssetEditorPresenter::onMaximumColorUpdated()
{

}

AssetEditorPresenter::AssetEditorPresenter(CommandHistory& commandHistory, AssetEditorWidget& widget, ConfettiInstance& confettiInstance) :
	Presenter(commandHistory),
	m_widget(widget),
	m_confettiInstance(confettiInstance)
{
	registerWidgetEvent("on_spawn_rate_updated", std::bind(&AssetEditorPresenter::onSpawnRateUpdated, this));
	registerWidgetEvent("on_minimum_lifetime_updated", std::bind(&AssetEditorPresenter::onMinimumLifetimeUpdated, this));
	registerWidgetEvent("on_maximum_lifetime_updated", std::bind(&AssetEditorPresenter::onMaximumLifetimeUpdated, this));
	registerWidgetEvent("on_minimum_position_updated", std::bind(&AssetEditorPresenter::onMinimumPositionUpdated, this));
	registerWidgetEvent("on_maximum_position_updated", std::bind(&AssetEditorPresenter::onMaximumPositionUpdated, this));
	registerWidgetEvent("on_minimum_velocity_updated", std::bind(&AssetEditorPresenter::onMinimumVelocityUpdated, this));
	registerWidgetEvent("on_maximum_velocity_updated", std::bind(&AssetEditorPresenter::onMaximumVelocityUpdated, this));
	registerWidgetEvent("on_minimum_scale_updated", std::bind(&AssetEditorPresenter::onMinimumScaleUpdated, this));
	registerWidgetEvent("on_maximum_scale_updated", std::bind(&AssetEditorPresenter::onMaximumScaleUpdated, this));
	registerWidgetEvent("on_minimum_color_updated", std::bind(&AssetEditorPresenter::onMinimumColorUpdated, this));
	registerWidgetEvent("on_maximum_color_updated", std::bind(&AssetEditorPresenter::onMaximumColorUpdated, this));
}