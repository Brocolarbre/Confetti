#pragma once

#include "UserInterface/Widget/AssetEditorWidget.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class AssetEditorPresenter : public Presenter
{
private:
	AssetEditorWidget& m_widget;
	ConfettiInstance& m_confettiInstance;

	void onParticleSystemSelected();
	void onParticleEffectSelected();
	void onParticleEmitterSelected();

	void onParticleSystemUpdated();
	void onParticleEffectUpdated();
	void onParticleEmitterUpdated();

public:
	AssetEditorPresenter(CommandHistory& commandHistory, AssetEditorWidget& widget, ConfettiInstance& confettiInstance);
};