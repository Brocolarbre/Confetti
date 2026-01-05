#include "ParticleRegistryWidget.hpp"

#include <imgui.h>
#include <format>

ParticleRegistryWidget::ParticleRegistryWidget() :
	WindowWidget("Particle Registry", false),
	m_particleSystems(),
	m_particleEffects(),
	m_particleEmitters(),
	m_selectedParticleSystem(),
	m_selectedParticleEffect(),
	m_selectedParticleEmitter(),
	m_renameBuffer()
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
			for (unsigned int i = 0; i < m_particleEmitters.size(); ++i)
			{
				bool selected = m_selectedParticleEmitter.has_value() && i == m_selectedParticleEmitter.value();
				std::string name = std::format("{}##{}", m_particleEmitters[i].name, m_particleEmitters[i].id);
				if (selected && m_renameBuffer.has_value())
				{
					ImGuiInputTextFlags flags = ImGuiInputFlags_None;
					if (m_renameBuffer.value().firstFrame)
					{
						flags |= ImGuiInputTextFlags_AutoSelectAll;
						ImGui::SetKeyboardFocusHere();
					}

					ImGui::InputText("##RenameTextBox", m_renameBuffer.value().buffer.data(), m_renameBuffer.value().buffer.size(), flags);
				}
				else if (ImGui::Selectable(name.c_str(), selected))
				{
					m_selectedParticleEmitter = std::make_optional(i);
					sendEvent("particle_emitter_selected");
				}

				if (ImGui::IsKeyPressed(ImGuiKey_F2) && !m_renameBuffer.has_value() && m_selectedParticleEmitter.has_value())
				{
					std::string buffer = std::string(256, '\0').replace(0, m_particleEmitters[i].name.size(), m_particleEmitters[i].name);
					m_renameBuffer = std::make_optional(RenameBuffer{ buffer, true });
				}

				if (ImGui::IsKeyPressed(ImGuiKey_Escape) && m_renameBuffer.has_value())
				{
					m_renameBuffer = std::nullopt;
				}

				if (ImGui::IsKeyPressed(ImGuiKey_Delete) && m_selectedParticleEmitter.has_value())
				{
					sendEvent("particle_emitter_destroyed");
					m_particleEmitters.erase(m_particleEmitters.begin() + m_selectedParticleEmitter.value());
					m_selectedParticleEmitter = std::nullopt;
					sendEvent("particle_emitter_selected");
					break;
				}

				if ((ImGui::IsKeyPressed(ImGuiKey_Enter) || ImGui::IsKeyPressed(ImGuiKey_KeypadEnter)) && m_renameBuffer.has_value())
				{
					const std::string& renameBuffer = m_renameBuffer.value().buffer;
					std::string newName = renameBuffer.substr(0, renameBuffer.find('\n', 0));
					if (!newName.empty())
					{
						m_particleEmitters[m_selectedParticleEmitter.value()].name = newName;
						m_renameBuffer = std::nullopt;
						sendEvent("particle_emitter_renamed");
					}
				}
			}

			if (ImGui::Button("Add"))
				sendEvent("particle_emitter_created");

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}