#pragma once

#include "WindowWidget.hpp"

#include <optional>

struct AssetEntry
{
	unsigned int id;
	std::string name;
};

class ParticleRegistryWidget : public WindowWidget
{
public:
	std::vector<AssetEntry> m_particleSystems;
	std::vector<AssetEntry> m_particleEffects;
	std::vector<AssetEntry> m_particleEmitters;

	std::optional<unsigned int> m_selectedParticleSystem;
	std::optional<unsigned int> m_selectedParticleEffect;
	std::optional<unsigned int> m_selectedParticleEmitter;

public:
	ParticleRegistryWidget();

	void render() override;
};