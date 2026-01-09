#include "AssetDictionary.hpp"

void AssetDictionary::setParticleSystemId(const std::string& name, unsigned int id)
{
    m_particleSystems[name] = id;
    sendEvent("particle_system_list_updated");
}

void AssetDictionary::setParticleEffectId(const std::string& name, unsigned int id)
{
    m_particleEffects[name] = id;
    sendEvent("particle_effect_list_updated");
}

void AssetDictionary::setParticleEmitterId(const std::string& name, unsigned int id)
{
    m_particleEmitters[name] = id;
    sendEvent("particle_emitter_list_updated");
}

void AssetDictionary::setForceFieldId(const std::string& name, unsigned int id)
{
    m_forceFields[name] = id;
    sendEvent("force_field_list_updated");
}

void AssetDictionary::removeParticleSystemId(const std::string& name)
{
    m_particleSystems.erase(name);
    sendEvent("particle_system_list_updated");
}

void AssetDictionary::removeParticleEffectId(const std::string& name)
{
    m_particleEffects.erase(name);
    sendEvent("particle_effect_list_updated");
}

void AssetDictionary::removeParticleEmitterId(const std::string& name)
{
    m_particleEmitters.erase(name);
    sendEvent("particle_emitter_list_updated");
}

void AssetDictionary::removeForceFieldId(const std::string& name)
{
    m_forceFields.erase(name);
    sendEvent("force_field_list_updated");
}

unsigned int AssetDictionary::getParticleSystemId(const std::string& name) const
{
    return m_particleSystems.at(name);
}

unsigned int AssetDictionary::getParticleEffectId(const std::string& name) const
{
    return m_particleEffects.at(name);
}

unsigned int AssetDictionary::getParticleEmitterId(const std::string& name) const
{
    return m_particleEmitters.at(name);
}

unsigned int AssetDictionary::getForceFieldId(const std::string& name) const
{
    return m_forceFields.at(name);
}

std::string AssetDictionary::getParticleSystemName(unsigned int id) const
{
    for (const auto& [systemName, systemId] : m_particleSystems)
    {
        if (id == systemId)
            return systemName;
    }

    return {};
}

std::string AssetDictionary::getParticleEffectName(unsigned int id) const
{
    for (const auto& [effectName, effectId] : m_particleEffects)
    {
        if (id == effectId)
            return effectName;
    }

    return {};
}

std::string AssetDictionary::getParticleEmitterName(unsigned int id) const
{
    for (const auto& [emitterName, emitterId] : m_particleEmitters)
    {
        if (id == emitterId)
            return emitterName;

    }

    return {};
}

std::string AssetDictionary::getForceFieldName(unsigned int id) const
{
    for (const auto& [forceFieldName, forceFieldId] : m_forceFields)
    {
        if (id == forceFieldId)
            return forceFieldName;

    }

    return {};
}

const std::unordered_map<std::string, unsigned int>& AssetDictionary::getParticleSystems() const
{
    return m_particleSystems;
}

const std::unordered_map<std::string, unsigned int>& AssetDictionary::getParticleEffects() const
{
    return m_particleEffects;
}

const std::unordered_map<std::string, unsigned int>& AssetDictionary::getParticleEmitters() const
{
    return m_particleEmitters;
}

const std::unordered_map<std::string, unsigned int>& AssetDictionary::getForceFields() const
{
    return m_forceFields;
}