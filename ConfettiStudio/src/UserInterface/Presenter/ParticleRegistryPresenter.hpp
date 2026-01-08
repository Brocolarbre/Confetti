#pragma once

#include "UserInterface/Widget/ParticleRegistryWidget.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class ParticleRegistryPresenter : public Presenter
{
private:
	ParticleRegistryWidget& m_widget;
	ConfettiInstance& m_confettiInstance;

	std::string findSuitableName(const std::string& name, const std::vector<std::string>& items) const;

	void onParticleSystemCreated();
	void onParticleEffectCreated();
	void onParticleEmitterCreated();

	void onParticleSystemDestroyed();
	void onParticleEffectDestroyed();
	void onParticleEmitterDestroyed();

	void onParticleSystemRenamed();
	void onParticleEffectRenamed();
	void onParticleEmitterRenamed();

	void onParticleSystemSelected();
	void onParticleEffectSelected();
	void onParticleEmitterSelected();

public:
	ParticleRegistryPresenter(CommandHistory& commandHistory, ParticleRegistryWidget& widget, ConfettiInstance& confettiInstance);
};