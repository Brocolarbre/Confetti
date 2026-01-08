#pragma once

#include "Model.hpp"

#include <optional>

class UserInterfaceState : public Model
{
private:
	std::optional<std::string> m_selectedParticleSystem;
	std::optional<std::string> m_selectedParticleEffect;
	std::optional<std::string> m_selectedParticleEmitter;

public:
	void setSelectedParticleSystem(const std::optional<std::string>& selectedParticleSystem);
	void setSelectedParticleEffect(const std::optional<std::string>& selectedParticleEffect);
	void setSelectedParticleEmitter(const std::optional<std::string>& selectedParticleEmitter);

	const std::optional<std::string>& getSelectedParticleSystem() const;
	const std::optional<std::string>& getSelectedParticleEffect() const;
	const std::optional<std::string>& getSelectedParticleEmitter() const;
};