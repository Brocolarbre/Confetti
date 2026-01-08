#include "UserInterfaceState.hpp"

void UserInterfaceState::setSelectedParticleSystem(const std::optional<std::string>& selectedParticleSystem)
{
    m_selectedParticleSystem = selectedParticleSystem;
    sendEvent("particle_system_selected");
}

void UserInterfaceState::setSelectedParticleEffect(const std::optional<std::string>& selectedParticleEffect)
{
    m_selectedParticleEffect = selectedParticleEffect;
    sendEvent("particle_effect_selected");
}

void UserInterfaceState::setSelectedParticleEmitter(const std::optional<std::string>& selectedParticleEmitter)
{
    m_selectedParticleEmitter = selectedParticleEmitter;
    sendEvent("particle_emitter_selected");
}

const std::optional<std::string>& UserInterfaceState::getSelectedParticleSystem() const
{
    return m_selectedParticleSystem;
}

const std::optional<std::string>& UserInterfaceState::getSelectedParticleEffect() const
{
    return m_selectedParticleEffect;
}

const std::optional<std::string>& UserInterfaceState::getSelectedParticleEmitter() const
{
    return m_selectedParticleEmitter;
}