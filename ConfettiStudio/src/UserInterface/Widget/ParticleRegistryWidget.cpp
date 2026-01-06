#include "ParticleRegistryWidget.hpp"

#include <imgui.h>
#include <format>

void ParticleRegistryWidget::sendParticleSystemCreatedEvent()
{
	sendEvent("particle_system_created");
}

void ParticleRegistryWidget::sendParticleSystemDestroyedEvent()
{
	sendEvent("particle_system_destroyed");
}

void ParticleRegistryWidget::sendParticleSystemRenamedEvent()
{
	sendEvent("particle_system_renamed");
}

void ParticleRegistryWidget::sendParticleSystemSelectedEvent()
{
	sendEvent("particle_system_selected");
}

void ParticleRegistryWidget::sendParticleEffectCreatedEvent()
{
	sendEvent("particle_effect_created");
}

void ParticleRegistryWidget::sendParticleEffectDestroyedEvent()
{
	sendEvent("particle_effect_destroyed");
}

void ParticleRegistryWidget::sendParticleEffectRenamedEvent()
{
	sendEvent("particle_effect_renamed");
}

void ParticleRegistryWidget::sendParticleEffectSelectedEvent()
{
	sendEvent("particle_effect_selected");
}

void ParticleRegistryWidget::sendParticleEmitterCreatedEvent()
{
	sendEvent("particle_emitter_created");
}

void ParticleRegistryWidget::sendParticleEmitterDestroyedEvent()
{
	sendEvent("particle_emitter_destroyed");
}

void ParticleRegistryWidget::sendParticleEmitterRenamedEvent()
{
	sendEvent("particle_emitter_renamed");
}

void ParticleRegistryWidget::sendParticleEmitterSelectedEvent()
{
	sendEvent("particle_emitter_selected");
}

ParticleRegistryWidget::ParticleRegistryWidget() :
	WindowWidget("Particle Registry", false),
	m_particleSystems("Systems", ItemListCallbacks{
		std::bind(&ParticleRegistryWidget::sendParticleSystemCreatedEvent, this),
		std::bind(&ParticleRegistryWidget::sendParticleSystemDestroyedEvent, this),
		std::bind(&ParticleRegistryWidget::sendParticleSystemRenamedEvent, this),
		std::bind(&ParticleRegistryWidget::sendParticleSystemSelectedEvent, this)
	}),
	m_particleEffects("Effects", ItemListCallbacks{
		std::bind(&ParticleRegistryWidget::sendParticleEffectCreatedEvent, this),
		std::bind(&ParticleRegistryWidget::sendParticleEffectDestroyedEvent, this),
		std::bind(&ParticleRegistryWidget::sendParticleEffectRenamedEvent, this),
		std::bind(&ParticleRegistryWidget::sendParticleEffectSelectedEvent, this)
	}),
	m_particleEmitters("Emitters", ItemListCallbacks{
		std::bind(&ParticleRegistryWidget::sendParticleEmitterCreatedEvent, this),
		std::bind(&ParticleRegistryWidget::sendParticleEmitterDestroyedEvent, this),
		std::bind(&ParticleRegistryWidget::sendParticleEmitterRenamedEvent, this),
		std::bind(&ParticleRegistryWidget::sendParticleEmitterSelectedEvent, this)
	}),
	m_activeTab(0)
{

}

void ParticleRegistryWidget::render()
{
	ImGuiID activeTab = 0;

	if (ImGui::BeginTabBar("Particle Assets"))
	{
		if (ImGui::BeginTabItem(m_particleSystems.getName().c_str()))
		{
			activeTab = ImGui::GetItemID();
			m_particleSystems.render();
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem(m_particleEffects.getName().c_str()))
		{
			activeTab = ImGui::GetItemID();
			m_particleEffects.render();
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem(m_particleEmitters.getName().c_str()))
		{
			activeTab = ImGui::GetItemID();
			m_particleEmitters.render(); // Add method in Widget to manually call a widget
			ImGui::EndTabItem();
		}

		if (activeTab != m_activeTab)
		{
			m_particleSystems.cancelRenaming();
			m_particleEffects.cancelRenaming();
			m_particleEmitters.cancelRenaming();
		}

		m_activeTab = activeTab;

		ImGui::EndTabBar();
	}
}