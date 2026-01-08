#include "AssetEditorPresenter.hpp"

void AssetEditorPresenter::onParticleSystemSelected()
{
	std::optional<unsigned int> selectedParticleSystem = m_confettiInstance.getUserInterfaceState().getSelectedParticleSystem();
	cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();

	if (selectedParticleSystem.has_value())
	{
		const cft::ParticleSystem& particleSystem = particleRegistry.getParticleSystem(selectedParticleSystem.value());
		m_widget.m_systemAsset = std::make_optional(SystemAsset{ particleSystem.effects });
	}
	else
	{
		m_widget.m_systemAsset = std::nullopt;
	}

	m_widget.m_effectAsset = std::nullopt;
	m_widget.m_emitterAsset = std::nullopt;
}

void AssetEditorPresenter::onParticleEffectSelected()
{
	std::optional<unsigned int> selectedParticleEffect = m_confettiInstance.getUserInterfaceState().getSelectedParticleEffect();
	cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();

	if (selectedParticleEffect.has_value())
	{
		const cft::ParticleEffect& particleEffect = particleRegistry.getParticleEffect(selectedParticleEffect.value());
		m_widget.m_effectAsset = std::make_optional(EffectAsset{ particleEffect.emitters });
	}
	else
	{
		m_widget.m_effectAsset = std::nullopt;
	}

	m_widget.m_systemAsset = std::nullopt;
	m_widget.m_emitterAsset = std::nullopt;
}

void AssetEditorPresenter::onParticleEmitterSelected()
{
	std::optional<unsigned int> selectedParticleEmitter = m_confettiInstance.getUserInterfaceState().getSelectedParticleEmitter();
	cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();

	if (selectedParticleEmitter.has_value())
	{
		const cft::ParticleEmitter& particleEmitter = particleRegistry.getParticleEmitter(selectedParticleEmitter.value());
		m_widget.m_emitterAsset = std::make_optional(EmitterAsset{
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
		m_widget.m_emitterAsset = std::nullopt;
	}

	m_widget.m_systemAsset = std::nullopt;
	m_widget.m_effectAsset = std::nullopt;
}

void AssetEditorPresenter::onParticleEffectListUpdated()
{
	const AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	m_widget.m_effectAssets.clear();
	m_widget.m_effectAssets.reserve(assetDictionary.getParticleEffects().size());
	for (const auto& [id, name] : assetDictionary.getParticleEffects())
		m_widget.m_effectAssets.push_back(Asset{ id, name });
}

void AssetEditorPresenter::onParticleEmitterListUpdated()
{
	const AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	m_widget.m_emitterAssets.clear();
	m_widget.m_emitterAssets.reserve(assetDictionary.getParticleEmitters().size());
	for (const auto& [id, name] : assetDictionary.getParticleEmitters())
		m_widget.m_emitterAssets.push_back(Asset{ id, name });
}

void AssetEditorPresenter::onParticleSystemUpdated()
{
	std::optional<unsigned int> selectedParticleSystem = m_confettiInstance.getUserInterfaceState().getSelectedParticleSystem();
	cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();

	if (selectedParticleSystem.has_value())
	{
		cft::ParticleSystem& particleSystem = particleRegistry.getParticleSystem(selectedParticleSystem.value());

		if (m_widget.m_systemAsset.has_value())
		{
			const SystemAsset& systemAsset = m_widget.m_systemAsset.value();
			particleSystem.effects = systemAsset.effects;
		}
	}
}

void AssetEditorPresenter::onParticleEffectUpdated()
{
	std::optional<unsigned int> selectedParticleEffect = m_confettiInstance.getUserInterfaceState().getSelectedParticleEffect();
	cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();

	if (selectedParticleEffect.has_value())
	{
		cft::ParticleEffect& particleEffect = particleRegistry.getParticleEffect(selectedParticleEffect.value());

		if (m_widget.m_effectAsset.has_value())
		{
			const EffectAsset& effectAsset = m_widget.m_effectAsset.value();
			particleEffect.emitters = effectAsset.emitters;
		}
	}
}

void AssetEditorPresenter::onParticleEmitterUpdated()
{
	std::optional<unsigned int> selectedParticleEmitter = m_confettiInstance.getUserInterfaceState().getSelectedParticleEmitter();
	cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();

	if (selectedParticleEmitter.has_value())
	{
		cft::ParticleEmitter& particleEmitter = particleRegistry.getParticleEmitter(selectedParticleEmitter.value());

		if (m_widget.m_emitterAsset.has_value())
		{
			const EmitterAsset& emitterAsset = m_widget.m_emitterAsset.value();

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