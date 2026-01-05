#include "ParticleRegistryPresenter.hpp"
#include "UserInterface/Command/CreateParticleEmitterCommand.hpp"
#include "UserInterface/Command/DestroyParticleEmitterCommand.hpp"
#include "UserInterface/Command/RenameParticleEmitterCommand.hpp"
#include "UserInterface/Command/SelectParticleEmitterCommand.hpp"

void ParticleRegistryPresenter::onParticleSystemCreated()
{

}

void ParticleRegistryPresenter::onParticleEffectCreated()
{

}

void ParticleRegistryPresenter::onParticleEmitterCreated()
{
	m_commandHistory.run<CreateParticleEmitterCommand>(m_confettiInstance);
	m_widget.m_particleEmitters.push_back(ParticleAsset{ m_confettiInstance.getIdGenerators().emitter.getLastId(), "Emitter" });
}

void ParticleRegistryPresenter::onParticleSystemDestroyed()
{

}

void ParticleRegistryPresenter::onParticleEffectDestroyed()
{

}

void ParticleRegistryPresenter::onParticleEmitterDestroyed()
{
	const ParticleAsset& particleAsset = m_widget.m_particleEmitters[m_widget.m_selectedParticleEmitter.value()];
	m_commandHistory.run<DestroyParticleEmitterCommand>(m_confettiInstance, particleAsset.id);
}

void ParticleRegistryPresenter::onParticleSystemRenamed()
{
	
}

void ParticleRegistryPresenter::onParticleEffectRenamed()
{

}

void ParticleRegistryPresenter::onParticleEmitterRenamed()
{
	const ParticleAsset& particleAsset = m_widget.m_particleEmitters[m_widget.m_selectedParticleEmitter.value()];
	m_commandHistory.run<RenameParticleEmitterCommand>(m_confettiInstance, particleAsset.id, particleAsset.name);
}

void ParticleRegistryPresenter::onParticleSystemSelected()
{

}

void ParticleRegistryPresenter::onParticleEffectSelected()
{

}

void ParticleRegistryPresenter::onParticleEmitterSelected()
{
	const ParticleAsset& particleAsset = m_widget.m_particleEmitters[m_widget.m_selectedParticleEmitter.value()];
	m_commandHistory.run<SelectParticleEmitterCommand>(m_confettiInstance, particleAsset.id);
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
	registerWidgetEvent("particle_system_renamed", std::bind(&ParticleRegistryPresenter::onParticleSystemRenamed, this));
	registerWidgetEvent("particle_effect_renamed", std::bind(&ParticleRegistryPresenter::onParticleEffectRenamed, this));
	registerWidgetEvent("particle_emitter_renamed", std::bind(&ParticleRegistryPresenter::onParticleEmitterRenamed, this));
	registerWidgetEvent("particle_system_selected", std::bind(&ParticleRegistryPresenter::onParticleSystemSelected, this));
	registerWidgetEvent("particle_effect_selected", std::bind(&ParticleRegistryPresenter::onParticleEffectSelected, this));
	registerWidgetEvent("particle_emitter_selected", std::bind(&ParticleRegistryPresenter::onParticleEmitterSelected, this));
}