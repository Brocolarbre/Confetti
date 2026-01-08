#include "AssetEditorPresenter.hpp"

void AssetEditorPresenter::onParticleSystemSelected()
{
	const std::optional<std::string>& selectedParticleSystem = m_confettiInstance.getUserInterfaceState().getSelectedParticleSystem();

	if (selectedParticleSystem.has_value())
	{
		const cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();
		const AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
		const cft::ParticleSystem& particleSystem = particleRegistry.getParticleSystem(assetDictionary.getParticleSystemId(selectedParticleSystem.value()));

		std::vector<std::string> particleEffects;
		particleEffects.reserve(particleSystem.effects.size());

		for (unsigned int particleEffectId : particleSystem.effects)
			particleEffects.push_back(assetDictionary.getParticleEffectName(particleEffectId));

		m_widget.m_system = std::make_optional(AssetEditorWidget::System{ particleEffects });
	}
	else
	{
		m_widget.m_system = std::nullopt;
	}

	m_widget.m_effect = std::nullopt;
	m_widget.m_emitter = std::nullopt;
}

void AssetEditorPresenter::onParticleEffectSelected()
{
	const std::optional<std::string>& selectedParticleEffect = m_confettiInstance.getUserInterfaceState().getSelectedParticleEffect();

	if (selectedParticleEffect.has_value())
	{
		const cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();
		const AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
		const cft::ParticleEffect& particleEffect = particleRegistry.getParticleEffect(assetDictionary.getParticleEffectId(selectedParticleEffect.value()));

		std::vector<std::string> particleEmitters;
		particleEmitters.reserve(particleEffect.emitters.size());

		for (unsigned int particleEmitterId : particleEffect.emitters)
			particleEmitters.push_back(assetDictionary.getParticleEmitterName(particleEmitterId));

		m_widget.m_effect = std::make_optional(AssetEditorWidget::Effect{ particleEmitters });
	}
	else
	{
		m_widget.m_effect = std::nullopt;
	}

	m_widget.m_system = std::nullopt;
	m_widget.m_emitter = std::nullopt;
}

void AssetEditorPresenter::onParticleEmitterSelected()
{
	const std::optional<std::string>& selectedParticleEmitter = m_confettiInstance.getUserInterfaceState().getSelectedParticleEmitter();

	if (selectedParticleEmitter.has_value())
	{
		const cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();
		const AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
		const cft::ParticleEmitter& particleEmitter = particleRegistry.getParticleEmitter(assetDictionary.getParticleEmitterId(selectedParticleEmitter.value()));

		m_widget.m_emitter = std::make_optional(AssetEditorWidget::Emitter{
			particleEmitter.spawnRate,
			particleEmitter.boundaries.minimumColor,
			particleEmitter.boundaries.maximumColor,
			particleEmitter.boundaries.minimumPosition,
			particleEmitter.boundaries.maximumPosition,
			particleEmitter.boundaries.minimumVelocity,
			particleEmitter.boundaries.maximumVelocity,
			particleEmitter.boundaries.minimumScale,
			particleEmitter.boundaries.maximumScale,
			particleEmitter.boundaries.minimumLifetime,
			particleEmitter.boundaries.maximumLifetime
		});
	}
	else
	{
		m_widget.m_emitter = std::nullopt;
	}

	m_widget.m_system = std::nullopt;
	m_widget.m_effect = std::nullopt;
}

void AssetEditorPresenter::onParticleEffectListUpdated()
{
	const AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	m_widget.m_effects.clear();
	m_widget.m_effects.reserve(assetDictionary.getParticleEffects().size());
	for (const auto& [name, id] : assetDictionary.getParticleEffects())
		m_widget.m_effects.push_back(name);
}

void AssetEditorPresenter::onParticleEmitterListUpdated()
{
	const AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	m_widget.m_emitters.clear();
	m_widget.m_emitters.reserve(assetDictionary.getParticleEmitters().size());
	for (const auto& [name, id] : assetDictionary.getParticleEmitters())
		m_widget.m_emitters.push_back(name);
}

void AssetEditorPresenter::onParticleSystemUpdated()
{
	const std::optional<std::string>& selectedParticleSystem = m_confettiInstance.getUserInterfaceState().getSelectedParticleSystem();

	if (selectedParticleSystem.has_value())
	{
		cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();
		const AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
		cft::ParticleSystem& particleSystem = particleRegistry.getParticleSystem(assetDictionary.getParticleSystemId(selectedParticleSystem.value()));

		if (m_widget.m_system.has_value())
		{
			const AssetEditorWidget::System& system = m_widget.m_system.value();
			std::vector<unsigned int> particleEffects;
			particleEffects.reserve(system.effects.size());

			for (const std::string& effect : system.effects)
				particleEffects.push_back(assetDictionary.getParticleEffectId(effect));

			particleSystem.effects = particleEffects;
		}
	}
}

void AssetEditorPresenter::onParticleEffectUpdated()
{
	const std::optional<std::string>& selectedParticleEffect = m_confettiInstance.getUserInterfaceState().getSelectedParticleEffect();

	if (selectedParticleEffect.has_value())
	{
		cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();
		const AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
		cft::ParticleEffect& particleEffect = particleRegistry.getParticleEffect(assetDictionary.getParticleEffectId(selectedParticleEffect.value()));

		if (m_widget.m_effect.has_value())
		{
			const AssetEditorWidget::Effect& effect = m_widget.m_effect.value();
			std::vector<unsigned int> particleEmitters;
			particleEmitters.reserve(effect.emitters.size());

			for (const std::string& emitter : effect.emitters)
				particleEmitters.push_back(assetDictionary.getParticleEffectId(emitter));

			particleEffect.emitters = particleEmitters;
		}
	}
}

void AssetEditorPresenter::onParticleEmitterUpdated()
{
	const std::optional<std::string>& selectedParticleEmitter = m_confettiInstance.getUserInterfaceState().getSelectedParticleEmitter();

	if (selectedParticleEmitter.has_value())
	{
		cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();
		const AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
		cft::ParticleEmitter& particleEmitter = particleRegistry.getParticleEmitter(assetDictionary.getParticleEmitterId(selectedParticleEmitter.value()));

		if (m_widget.m_emitter.has_value())
		{
			const AssetEditorWidget::Emitter& emitterAsset = m_widget.m_emitter.value();

			particleEmitter.spawnRate = emitterAsset.spawnRate;
			particleEmitter.boundaries.minimumColor = emitterAsset.minimumColor;
			particleEmitter.boundaries.maximumColor = emitterAsset.maximumColor;
			particleEmitter.boundaries.minimumPosition = emitterAsset.minimumPosition;
			particleEmitter.boundaries.maximumPosition = emitterAsset.maximumPosition;
			particleEmitter.boundaries.minimumVelocity = emitterAsset.minimumVelocity;
			particleEmitter.boundaries.maximumVelocity = emitterAsset.maximumVelocity;
			particleEmitter.boundaries.minimumScale = emitterAsset.minimumScale;
			particleEmitter.boundaries.minimumScale = emitterAsset.minimumScale;
			particleEmitter.boundaries.maximumLifetime = emitterAsset.maximumLifetime;
			particleEmitter.boundaries.maximumLifetime = emitterAsset.maximumLifetime;
		}
	}
}

AssetEditorPresenter::AssetEditorPresenter(CommandHistory& commandHistory, AssetEditorWidget& widget, ConfettiInstance& confettiInstance) :
	Presenter(commandHistory),
	m_widget(widget),
	m_confettiInstance(confettiInstance)
{
	registerModelEvent("particle_system_selected", std::bind(&AssetEditorPresenter::onParticleSystemSelected, this));
	registerModelEvent("particle_effect_selected", std::bind(&AssetEditorPresenter::onParticleEffectSelected, this));
	registerModelEvent("particle_emitter_selected", std::bind(&AssetEditorPresenter::onParticleEmitterSelected, this));
	registerModelEvent("particle_effect_list_updated", std::bind(&AssetEditorPresenter::onParticleEffectListUpdated, this));
	registerModelEvent("particle_emitter_list_updated", std::bind(&AssetEditorPresenter::onParticleEmitterListUpdated, this));

	registerWidgetEvent("particle_system_updated", std::bind(&AssetEditorPresenter::onParticleSystemUpdated, this));
	registerWidgetEvent("particle_effect_updated", std::bind(&AssetEditorPresenter::onParticleEffectUpdated, this));
	registerWidgetEvent("particle_emitter_updated", std::bind(&AssetEditorPresenter::onParticleEmitterUpdated, this));
}