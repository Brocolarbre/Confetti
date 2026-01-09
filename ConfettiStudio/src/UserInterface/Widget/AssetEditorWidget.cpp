#include "AssetEditorWidget.hpp"

#include <imgui.h>
#include <format>

AssetEditorWidget::AssetEditorWidget() :
	WindowWidget("Asset Editor", false),
	m_emitter(),
	m_effect(),
	m_system(),
	m_selectedEffect(),
	m_selectedEmitter(),
	m_selectedNewEffect(),
	m_selectedNewEmitter(),
	m_effects(),
	m_emitters()
{

}

void AssetEditorWidget::render()
{
	if (m_emitter.has_value())
	{
		Emitter& emitter = m_emitter.value();
		ImGui::SeparatorText("Particle Emitter");

		if (ImGui::InputFloat("Spawn rate", &emitter.spawnRate, 0.0f, 0.0f, "%.2f"))
		{
			if (emitter.spawnRate < 0.0f)
				emitter.spawnRate = 0.0f;

			sendEvent("particle_emitter_updated");
		}

		if (ImGui::InputFloat("Minimum lifetime", &emitter.minimumLifetime))
		{
			if (emitter.minimumLifetime < 0.0f)
				emitter.minimumLifetime = 0.0f;

			sendEvent("particle_emitter_updated");
		}

		if (ImGui::InputFloat("Maximum lifetime", &emitter.maximumLifetime))
			sendEvent("particle_emitter_updated");

		if (ImGui::InputFloat3("Minimum position", &emitter.minimumPosition[0]))
			sendEvent("particle_emitter_updated");

		if (ImGui::InputFloat3("Maximum position", &emitter.maximumPosition[0]))
			sendEvent("particle_emitter_updated");

		if (ImGui::InputFloat3("Minimum velocity", &emitter.minimumVelocity[0]))
			sendEvent("particle_emitter_updated");

		if (ImGui::InputFloat3("Maximum velocity", &emitter.maximumVelocity[0]))
			sendEvent("particle_emitter_updated");

		if (ImGui::InputFloat3("Minimum scale", &emitter.minimumScale[0]))
			sendEvent("particle_emitter_updated");

		if (ImGui::InputFloat3("Maximum scale", &emitter.maximumScale[0]))
			sendEvent("particle_emitter_updated");

		if (ImGui::InputFloat4("Minimum color", &emitter.minimumColor[0]))
			sendEvent("particle_emitter_updated");

		if (ImGui::InputFloat4("Maximum color", &emitter.maximumColor[0]))
			sendEvent("particle_emitter_updated");
	}
	else if (m_effect.has_value())
	{
		Effect& effect = m_effect.value();

		for (unsigned int i = 0; i < effect.emitters.size(); ++i)
		{
			if (ImGui::Selectable(std::format("{}##{}", effect.emitters[i], i).c_str(), m_selectedEmitter.has_value() ? i == m_selectedEmitter.value() : false))
			{
				m_selectedEmitter = std::make_optional(i);
			}
		}

		std::string selectedEmitter = m_selectedNewEmitter.value_or("");
		if (ImGui::BeginCombo("Emitter", selectedEmitter.empty() ? "Select" : selectedEmitter.c_str()))
		{
			for (const std::string& emitter : m_emitters)
			{
				if (ImGui::Selectable(emitter.c_str(), emitter == selectedEmitter))
				{
					m_selectedNewEmitter = std::make_optional(emitter);
					break;
				}
			}

			ImGui::EndCombo();
		}

		ImGui::SameLine();
		ImGui::BeginDisabled(!m_selectedNewEmitter.has_value());
		if (ImGui::Button("Add"))
		{
			effect.emitters.push_back(m_selectedNewEmitter.value());
			m_selectedNewEmitter = std::nullopt;
			m_selectedEmitter = std::make_optional(static_cast<unsigned int>(effect.emitters.size() - 1));
			sendEvent("particle_effect_updated");
		}
		ImGui::EndDisabled();

		if (ImGui::IsWindowFocused())
		{
			if (ImGui::IsKeyPressed(ImGuiKey_Delete) && m_selectedEmitter.has_value())
			{
				effect.emitters.erase(effect.emitters.begin() + m_selectedEmitter.value());
				m_selectedEmitter = std::nullopt;
				sendEvent("particle_effect_updated");
			}
		}
	}
	else if (m_system.has_value())
	{
		System& system = m_system.value();

		for (unsigned int i = 0; i < system.effects.size(); ++i)
		{
			if (ImGui::Selectable(std::format("{}##{}", system.effects[i], i).c_str(), m_selectedEffect.has_value() ? i == m_selectedEffect.value() : false))
			{
				m_selectedEffect = std::make_optional(i);
			}
		}

		std::string selectedEffect = m_selectedNewEffect.value_or("");
		if (ImGui::BeginCombo("Effect", selectedEffect.empty() ? "Select" : selectedEffect.c_str()))
		{
			for (const std::string& effect : m_effects)
			{
				if (ImGui::Selectable(effect.c_str(), effect == selectedEffect))
				{
					m_selectedNewEffect = std::make_optional(effect);
					break;
				}
			}

			ImGui::EndCombo();
		}

		ImGui::SameLine();
		ImGui::BeginDisabled(!m_selectedNewEffect.has_value());
		if (ImGui::Button("Add"))
		{
			system.effects.push_back(m_selectedNewEffect.value());
			m_selectedNewEffect = std::nullopt;
			m_selectedEffect = std::make_optional(static_cast<unsigned int>(system.effects.size() - 1));
			sendEvent("particle_system_updated");
		}
		ImGui::EndDisabled();

		if (ImGui::IsWindowFocused())
		{
			if (ImGui::IsKeyPressed(ImGuiKey_Delete) && m_selectedEffect.has_value())
			{
				system.effects.erase(system.effects.begin() + m_selectedEffect.value());
				m_selectedEffect = std::nullopt;
				sendEvent("particle_system_updated");
			}
		}
	}
}