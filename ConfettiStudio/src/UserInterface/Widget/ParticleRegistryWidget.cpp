#include "ParticleRegistryWidget.hpp"

#include <imgui.h>

ParticleRegistryWidget::ParticleRegistryWidget() :
	WindowWidget("Particle Registry", false),
	m_particleSystems(),
	m_particleEffects(),
	m_particleEmitters(),
	m_selectedParticleSystem(),
	m_selectedParticleEffect(),
	m_selectedParticleEmitter()
{

}

void ParticleRegistryWidget::render()
{
	if (ImGui::BeginTabBar("Particle Assets"))
	{
		if (ImGui::BeginTabItem("Systems"))
		{
			

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Effects"))
		{


			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Emitters"))
		{
			for (unsigned int particleEmitter : m_particleEmitters)
				ImGui::Text("%d", particleEmitter);

			if (ImGui::Button("Add"))
				sendEvent("particle_emitter_created");

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}