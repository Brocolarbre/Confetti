#include "ParticleRegistryPresenter.hpp"
#include "UserInterface/Command/CreateParticleSystemCommand.hpp"
#include "UserInterface/Command/CreateParticleEffectCommand.hpp"
#include "UserInterface/Command/CreateParticleEmitterCommand.hpp"
#include "UserInterface/Command/DestroyParticleSystemCommand.hpp"
#include "UserInterface/Command/DestroyParticleEffectCommand.hpp"
#include "UserInterface/Command/DestroyParticleEmitterCommand.hpp"
#include "UserInterface/Command/RenameParticleSystemCommand.hpp"
#include "UserInterface/Command/RenameParticleEffectCommand.hpp"
#include "UserInterface/Command/RenameParticleEmitterCommand.hpp"
#include "UserInterface/Command/SelectParticleSystemCommand.hpp"
#include "UserInterface/Command/SelectParticleEffectCommand.hpp"
#include "UserInterface/Command/SelectParticleEmitterCommand.hpp"

void ParticleRegistryPresenter::onParticleSystemCreated()
{
	m_commandHistory.run<CreateParticleSystemCommand>(m_confettiInstance);
	m_widget.m_particleSystems.push_back(ParticleAsset{ m_confettiInstance.getIdGenerators().system.getLastId(), "System" });
}

void ParticleRegistryPresenter::onParticleEffectCreated()
{
	m_commandHistory.run<CreateParticleEffectCommand>(m_confettiInstance);
	m_widget.m_particleEffects.push_back(ParticleAsset{ m_confettiInstance.getIdGenerators().effect.getLastId(), "Effect" });
}

void ParticleRegistryPresenter::onParticleEmitterCreated()
{
	m_commandHistory.run<CreateParticleEmitterCommand>(m_confettiInstance);
	m_widget.m_particleEmitters.push_back(ParticleAsset{ m_confettiInstance.getIdGenerators().emitter.getLastId(), "Emitter" });
}

void ParticleRegistryPresenter::onParticleSystemDestroyed()
{
	const ParticleAsset& particleAsset = m_widget.m_particleSystems[m_widget.m_selectedParticleSystem.value()];
	m_commandHistory.run<DestroyParticleSystemCommand>(m_confettiInstance, particleAsset.id);
}

void ParticleRegistryPresenter::onParticleEffectDestroyed()
{
	const ParticleAsset& particleAsset = m_widget.m_particleEffects[m_widget.m_selectedParticleEffect.value()];
	m_commandHistory.run<DestroyParticleEffectCommand>(m_confettiInstance, particleAsset.id);
}

void ParticleRegistryPresenter::onParticleEmitterDestroyed()
{
	const ParticleAsset& particleAsset = m_widget.m_particleEmitters[m_widget.m_selectedParticleEmitter.value()];
	m_commandHistory.run<DestroyParticleEmitterCommand>(m_confettiInstance, particleAsset.id);
}

void ParticleRegistryPresenter::onParticleSystemRenamed()
{
	const ParticleAsset& particleAsset = m_widget.m_particleSystems[m_widget.m_selectedParticleSystem.value()];
	m_commandHistory.run<RenameParticleSystemCommand>(m_confettiInstance, particleAsset.id, particleAsset.name);
}

void ParticleRegistryPresenter::onParticleEffectRenamed()
{
	const ParticleAsset& particleAsset = m_widget.m_particleEffects[m_widget.m_selectedParticleEffect.value()];
	m_commandHistory.run<RenameParticleEffectCommand>(m_confettiInstance, particleAsset.id, particleAsset.name);
}

void ParticleRegistryPresenter::onParticleEmitterRenamed()
{
	const ParticleAsset& particleAsset = m_widget.m_particleEmitters[m_widget.m_selectedParticleEmitter.value()];
	m_commandHistory.run<RenameParticleEmitterCommand>(m_confettiInstance, particleAsset.id, particleAsset.name);
}

void ParticleRegistryPresenter::onParticleSystemSelected()
{
	if (m_widget.m_selectedParticleSystem.has_value())
	{
		const ParticleAsset& particleAsset = m_widget.m_particleSystems[m_widget.m_selectedParticleSystem.value()];
		m_commandHistory.run<SelectParticleSystemCommand>(m_confettiInstance, particleAsset.id);
	}
	else
	{
		m_commandHistory.run<SelectParticleSystemCommand>(m_confettiInstance, std::nullopt);
	}
}

void ParticleRegistryPresenter::onParticleEffectSelected()
{
	if (m_widget.m_selectedParticleEffect.has_value())
	{
		const ParticleAsset& particleAsset = m_widget.m_particleEffects[m_widget.m_selectedParticleEffect.value()];
		m_commandHistory.run<SelectParticleEffectCommand>(m_confettiInstance, particleAsset.id);
	}
	else
	{
		m_commandHistory.run<SelectParticleEffectCommand>(m_confettiInstance, std::nullopt);
	}
}

void ParticleRegistryPresenter::onParticleEmitterSelected()
{
	if (m_widget.m_selectedParticleEmitter.has_value())
	{
		const ParticleAsset& particleAsset = m_widget.m_particleEmitters[m_widget.m_selectedParticleEmitter.value()];
		m_commandHistory.run<SelectParticleEmitterCommand>(m_confettiInstance, particleAsset.id);
	}
	else
	{
		m_commandHistory.run<SelectParticleEmitterCommand>(m_confettiInstance, std::nullopt);
	}
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