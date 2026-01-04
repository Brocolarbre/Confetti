#pragma once

#include "UserInterface/Widget/ParticleRegistryWidget.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class ParticleRegistryPresenter : public Presenter
{
private:
	ParticleRegistryWidget& m_widget;
	ConfettiInstance& m_confettiInstance;

	void onParticleSystemCreated();
	void onParticleEffectCreated();
	void onParticleEmitterCreated();

	void onParticleSystemDestroyed();
	void onParticleEffectDestroyed();
	void onParticleEmitterDestroyed();

public:
	ParticleRegistryPresenter(CommandHistory& commandHistory, ParticleRegistryWidget& widget, ConfettiInstance& confettiInstance);
};