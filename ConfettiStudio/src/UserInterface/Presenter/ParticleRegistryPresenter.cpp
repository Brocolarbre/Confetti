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

#include <format>

std::string ParticleRegistryPresenter::findSuitableName(const std::string& name, const std::vector<std::string>& items) const
{
	if (items.empty())
		return name;

	std::string suitableName = name;
	unsigned int duplicateCount = 0;
	bool duplicate = true;
	while (duplicate)
	{
		duplicate = false;

		for (const std::string& item : items)
		{
			if (item == suitableName)
			{
				suitableName = std::format("{}_{}", name, ++duplicateCount);
				duplicate = true;
				break;
			}
		}
	}

	return suitableName;
}

void ParticleRegistryPresenter::onParticleSystemCreated()
{
	std::string name = findSuitableName("System", m_widget.m_particleSystems.getItems());
	m_commandHistory.run<CreateParticleSystemCommand>(m_confettiInstance, name);
	m_widget.m_particleSystems.addItem(name);
}

void ParticleRegistryPresenter::onParticleEffectCreated()
{
	std::string name = findSuitableName("Effect", m_widget.m_particleEffects.getItems());
	m_commandHistory.run<CreateParticleEffectCommand>(m_confettiInstance, name);
	m_widget.m_particleEffects.addItem(name);
}

void ParticleRegistryPresenter::onParticleEmitterCreated()
{
	std::string name = findSuitableName("Emitter", m_widget.m_particleEmitters.getItems());
	m_commandHistory.run<CreateParticleEmitterCommand>(m_confettiInstance, name);
	m_widget.m_particleEmitters.addItem(name);
}

void ParticleRegistryPresenter::onParticleSystemDestroyed()
{
	const std::string& particleSystem = m_widget.m_particleSystems.getItems()[m_widget.m_particleSystems.getSelectedItem().value()];
	m_commandHistory.run<DestroyParticleSystemCommand>(m_confettiInstance, particleSystem);
}

void ParticleRegistryPresenter::onParticleEffectDestroyed()
{
	const std::string& particleEffect = m_widget.m_particleEffects.getItems()[m_widget.m_particleEffects.getSelectedItem().value()];
	m_commandHistory.run<DestroyParticleEffectCommand>(m_confettiInstance, particleEffect);
}

void ParticleRegistryPresenter::onParticleEmitterDestroyed()
{
	const std::string& particleEmitter = m_widget.m_particleEmitters.getItems()[m_widget.m_particleEmitters.getSelectedItem().value()];
	m_commandHistory.run<DestroyParticleEmitterCommand>(m_confettiInstance, particleEmitter);
}

void ParticleRegistryPresenter::onParticleSystemRenamed()
{
	const std::string& particleSystem = m_widget.m_particleSystems.getPreviousItemName();
	m_commandHistory.run<RenameParticleSystemCommand>(m_confettiInstance, particleSystem, m_widget.m_particleSystems.getItems()[m_widget.m_particleSystems.getSelectedItem().value()]);
}

void ParticleRegistryPresenter::onParticleEffectRenamed()
{
	const std::string& particleEffect = m_widget.m_particleEffects.getPreviousItemName();
	m_commandHistory.run<RenameParticleEffectCommand>(m_confettiInstance, particleEffect, m_widget.m_particleEffects.getItems()[m_widget.m_particleEffects.getSelectedItem().value()]);
}

void ParticleRegistryPresenter::onParticleEmitterRenamed()
{
	const std::string& particleEmitter = m_widget.m_particleEmitters.getPreviousItemName();
	m_commandHistory.run<RenameParticleEmitterCommand>(m_confettiInstance, particleEmitter, m_widget.m_particleEmitters.getItems()[m_widget.m_particleEmitters.getSelectedItem().value()]);
}

void ParticleRegistryPresenter::onParticleSystemSelected()
{
	if (m_widget.m_particleSystems.getSelectedItem().has_value())
	{
		const std::string& particleSystem = m_widget.m_particleSystems.getItems()[m_widget.m_particleSystems.getSelectedItem().value()];
		m_commandHistory.run<SelectParticleSystemCommand>(m_confettiInstance, particleSystem);
	}
	else
	{
		m_commandHistory.run<SelectParticleSystemCommand>(m_confettiInstance, std::nullopt);
	}
}

void ParticleRegistryPresenter::onParticleEffectSelected()
{
	if (m_widget.m_particleEffects.getSelectedItem().has_value())
	{
		const std::string& particleEffect = m_widget.m_particleEffects.getItems()[m_widget.m_particleEffects.getSelectedItem().value()];
		m_commandHistory.run<SelectParticleEffectCommand>(m_confettiInstance, particleEffect);
	}
	else
	{
		m_commandHistory.run<SelectParticleEffectCommand>(m_confettiInstance, std::nullopt);
	}
}

void ParticleRegistryPresenter::onParticleEmitterSelected()
{
	if (m_widget.m_particleEmitters.getSelectedItem().has_value())
	{
		const std::string& particleEmitter = m_widget.m_particleEmitters.getItems()[m_widget.m_particleEmitters.getSelectedItem().value()];
		m_commandHistory.run<SelectParticleEmitterCommand>(m_confettiInstance, particleEmitter);
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