#include "AssetEditorWidget.hpp"

#include <imgui.h>
#include <format>

AssetEditorWidget::AssetEditorWidget() :
	WindowWidget("Asset Editor", false),
	m_emitterAsset(),
	m_effectAsset(),
	m_systemAsset(),
	m_effectAssets(),
	m_emitterAssets()
{

}

void AssetEditorWidget::render()
{
	if (m_emitterAsset.has_value())
	{
		EmitterAsset& emitter = m_emitterAsset.value();
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
	else if (m_effectAsset.has_value())
	{
		// Make names unique, two way dictionary, code simplification, add number suffix on new asset names
		EffectAsset& effect = m_effectAsset.value();
		for (unsigned int emitter : effect.emitters)
		{
			ImGui::Text(std::format("{}##{}", emitter.name, emitter.id).c_str());
			ImGui::SameLine();
		}


		for (const Asset& emitter : m_emitterAssets)
		{
			
		}
	}
	else if (m_systemAsset.has_value())
	{

	}
}