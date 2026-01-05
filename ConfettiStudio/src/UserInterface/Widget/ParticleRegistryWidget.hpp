#pragma once

#include "WindowWidget.hpp"

#include <optional>

struct ParticleAsset
{
	unsigned int id;
	std::string name;
};

struct RenameBuffer
{
	std::string buffer;
	bool firstFrame;
};

class ParticleRegistryWidget : public WindowWidget
{
public:
	std::vector<ParticleAsset> m_particleSystems;
	std::vector<ParticleAsset> m_particleEffects;
	std::vector<ParticleAsset> m_particleEmitters;

	std::optional<unsigned int> m_selectedParticleSystem;
	std::optional<unsigned int> m_selectedParticleEffect;
	std::optional<unsigned int> m_selectedParticleEmitter;

	std::optional<RenameBuffer> m_renameBuffer;

public:
	ParticleRegistryWidget();

	void render() override;
};