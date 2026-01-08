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

struct EffectAsset
{
	std::vector<unsigned int> emitters;
};

struct SystemAsset
{
	std::vector<unsigned int> effects;
};

struct Asset
{
	unsigned int id;
	std::string name;
};

class AssetEditorWidget : public WindowWidget
{
public:
	std::optional<EmitterAsset> m_emitterAsset;
	std::optional<EffectAsset> m_effectAsset;
	std::optional<SystemAsset> m_systemAsset;

	std::vector<Asset> m_effectAssets;
	std::vector<Asset> m_emitterAssets;

public:
	AssetEditorWidget();

	void render() override;
};