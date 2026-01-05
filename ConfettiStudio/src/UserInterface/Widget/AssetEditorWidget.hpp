#pragma once

#include "WindowWidget.hpp"

#include <optional>

struct EmitterAsset
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

class AssetEditorWidget : public WindowWidget
{
private:
	std::optional<EmitterAsset> m_emitterAsset;

public:
	AssetEditorWidget();

	void render() override;
};