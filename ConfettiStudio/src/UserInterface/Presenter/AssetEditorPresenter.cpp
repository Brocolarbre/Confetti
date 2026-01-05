#include "AssetEditorPresenter.hpp"

void AssetEditorPresenter::onParticleSystemSelected()
{

}

void AssetEditorPresenter::onParticleEffectSelected()
{

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

	registerWidgetEvent("particle_emitter_updated", std::bind(&AssetEditorPresenter::onParticleEmitterUpdated, this));
}