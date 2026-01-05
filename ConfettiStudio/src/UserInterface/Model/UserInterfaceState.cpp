#include "UserInterfaceState.hpp"

void UserInterfaceState::setSelectedParticleSystem(const std::optional<unsigned int>& selectedParticleSystem)
{
    m_selectedParticleSystem = selectedParticleSystem;
    sendEvent("particle_system_selected");
}

void UserInterfaceState::setSelectedParticleEffect(const std::optional<unsigned int>& selectedParticleEffect)
{
    m_selectedParticleEffect = selectedParticleEffect;
    sendEvent("particle_effect_selected");
}

void UserInterfaceState::setSelectedParticleEmitter(const std::optional<unsigned int>& selectedParticleEmitter)
{
    m_selectedParticleEmitter = selectedParticleEmitter;
    sendEvent("particle_emitter_selected");
}

std::optional<unsigned int> UserInterfaceState::getSelectedParticleSystem() const
{
    return m_selectedParticleSystem;
}

std::optional<unsigned int> UserInterfaceState::getSelectedParticleEffect() const
{
    return m_selectedParticleEffect;
}

std::optional<unsigned int> UserInterfaceState::getSelectedParticleEmitter() const
{
    return m_selectedParticleEmitter;
}