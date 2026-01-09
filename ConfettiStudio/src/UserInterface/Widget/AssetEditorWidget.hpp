#pragma once

#include "WindowWidget.hpp"

#include <optional>

class AssetEditorWidget : public WindowWidget
{
public:
	struct Emitter
	{
		float spawnRate;
		glm::vec4 minimumColor;
		glm::vec4 maximumColor;
		glm::vec3 minimumPosition;
		glm::vec3 maximumPosition;
		glm::vec3 minimumVelocity;
		glm::vec3 maximumVelocity;
		glm::vec2 minimumScale;
		glm::vec2 maximumScale;
		float minimumLifetime;
		float maximumLifetime;
	};

	struct Effect
	{
		std::vector<std::string> emitters;
	};

	struct System
	{
		std::vector<std::string> effects;
	};

	std::optional<Emitter> m_emitter;
	std::optional<Effect> m_effect;
	std::optional<System> m_system;

	std::optional<std::string> m_selectedEffect;
	std::optional<std::string> m_selectedEmitter;

	std::vector<std::string> m_effects;
	std::vector<std::string> m_emitters;

public:
	AssetEditorWidget();

	void render() override;
};