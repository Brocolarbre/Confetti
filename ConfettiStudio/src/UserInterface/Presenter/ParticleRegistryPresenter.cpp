#include "ParticleRegistryPresenter.hpp"
#include "UserInterface/Command/CreateParticleEmitterCommand.hpp"
#include "UserInterface/Command/DestroyParticleEmitterCommand.hpp"

void ParticleRegistryPresenter::onParticleSystemCreated()
{

}

void ParticleRegistryPresenter::onParticleEffectCreated()
{

}

void ParticleRegistryPresenter::onParticleEmitterCreated()
{
	m_commandHistory.run<CreateParticleEmitterCommand>(m_confettiInstance);
	m_widget.m_particleEmitters.push_back();
}

void ParticleRegistryPresenter::onParticleSystemDestroyed()
{

}

void ParticleRegistryPresenter::onParticleEffectDestroyed()
{

}

void ParticleRegistryPresenter::onParticleEmitterDestroyed()
{
	m_commandHistory.run<DestroyParticleEmitterCommand>(m_confettiInstance, m_widget.m_selectedParticleEmitter.value());
}

ParticleRegistryPresenter::ParticleRegistryPresenter(CommandHistory& commandHistory, ParticleRegistryWidget& widget, ConfettiInstance& confettiInstance) :
	Presenter(commandHistory),
	m_widget(widget),
	m_confettiInstance(confettiInstance)
{
	registerWidgetEvent("particle_system_created", std::bind(&ParticleRegistryPresenter::onParticleSystemCreated, this));
	registerWidgetEvent("particle_effect_created", std::bind(&ParticleRegistryPresenter::onParticleEffectCreated, this));
	registerWidgetEvent("particle_emitter_created", std::bind(&ParticleRegistryPresenter::onParticleEmitterCreated, this));
	registerWidgetEvent("particle_system_destroyed", std::bind(&ParticleRegistryPresenter::onParticleSystemDestroyed, this));
	registerWidgetEvent("particle_effect_destroyed", std::bind(&ParticleRegistryPresenter::onParticleEffectDestroyed, this));
	registerWidgetEvent("particle_emitter_destroyed", std::bind(&ParticleRegistryPresenter::onParticleEmitterDestroyed, this));
}