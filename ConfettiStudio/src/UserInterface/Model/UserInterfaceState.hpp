#pragma once

#include "Model.hpp"

#include <optional>

class UserInterfaceState : public Model
{
private:
	std::optional<unsigned int> m_selectedParticleSystem;
	std::optional<unsigned int> m_selectedParticleEffect;
	std::optional<unsigned int> m_selectedParticleEmitter;

public:
	void setSelectedParticleSystem(const std::optional<unsigned int>& selectedParticleSystem);
	void setSelectedParticleEffect(const std::optional<unsigned int>& selectedParticleEffect);
	void setSelectedParticleEmitter(const std::optional<unsigned int>& selectedParticleEmitter);

	std::optional<unsigned int> getSelectedParticleSystem() const;
	std::optional<unsigned int> getSelectedParticleEffect() const;
	std::optional<unsigned int> getSelectedParticleEmitter() const;
};