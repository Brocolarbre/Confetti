#pragma once

#include "WindowWidget.hpp"
#include "ItemListWidget.hpp"

class ParticleRegistryWidget : public WindowWidget
{
public:
	ItemListWidget m_particleSystems;
	ItemListWidget m_particleEffects;
	ItemListWidget m_particleEmitters;

	unsigned int m_activeTab;

	void sendParticleSystemCreatedEvent();
	void sendParticleSystemDestroyedEvent();
	void sendParticleSystemRenamedEvent();
	void sendParticleSystemSelectedEvent();

	void sendParticleEffectCreatedEvent();
	void sendParticleEffectDestroyedEvent();
	void sendParticleEffectRenamedEvent();
	void sendParticleEffectSelectedEvent();

	void sendParticleEmitterCreatedEvent();
	void sendParticleEmitterDestroyedEvent();
	void sendParticleEmitterRenamedEvent();
	void sendParticleEmitterSelectedEvent();

public:
	ParticleRegistryWidget();

	void render() override;
};