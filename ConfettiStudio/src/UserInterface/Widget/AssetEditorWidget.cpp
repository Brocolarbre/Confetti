#include "AssetEditorWidget.hpp"

#include <imgui.h>
#include <format>

AssetEditorWidget::AssetEditorWidget() :
	WindowWidget("Asset Editor", false),
	m_emitter(),
	m_effect(),
	m_system(),
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
		/*Effect& effect = m_effect.value();
		for (unsigned int emitter : effect.emitters)
		{
			ImGui::Text(std::format("{}##{}", emitter.name, emitter.id).c_str());
			ImGui::SameLine();
		}


		for (const Asset& emitter : m_emitters)
		{
			
		}*/
	}
	else if (m_system.has_value())
	{

	}
}