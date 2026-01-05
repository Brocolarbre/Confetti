#include "AssetEditorWidget.hpp"

#include <imgui.h>

AssetEditorWidget::AssetEditorWidget() :
	WindowWidget("Asset Editor", false)
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
}