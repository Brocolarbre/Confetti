#include "AssetDictionary.hpp"

void AssetDictionary::setParticleSystemName(unsigned int id, const std::string& name)
{
    m_particleSystems[id] = name;
    sendEvent("particle_system_list_updated");
}

void AssetDictionary::setParticleEffectName(unsigned int id, const std::string& name)
{
    m_particleEffects[id] = name;
    sendEvent("particle_effect_list_updated");
}

void AssetDictionary::setParticleEmitterName(unsigned int id, const std::string& name)
{
    m_particleEmitters[id] = name;
    sendEvent("particle_emitter_list_updated");
}

void AssetDictionary::removeParticleSystemName(unsigned int id)
{
    m_particleSystems.erase(id);
    sendEvent("particle_system_list_updated");
}

void AssetDictionary::removeParticleEffectName(unsigned int id)
{
    m_particleEffects.erase(id);
    sendEvent("particle_effect_list_updated");
}

void AssetDictionary::removeParticleEmitterName(unsigned int id)
{
    m_particleEmitters.erase(id);
    sendEvent("particle_emitter_list_updated");
}

const std::string& AssetDictionary::getParticleSystemName(unsigned int id) const
{
    return m_particleSystems.at(id);
}

const std::string& AssetDictionary::getParticleEffectName(unsigned int id) const
{
    return m_particleEffects.at(id);
}

const std::string& AssetDictionary::getParticleEmitterName(unsigned int id) const
{
    return m_particleEmitters.at(id);
}

const std::unordered_map<unsigned int, std::string>& AssetDictionary::getParticleSystems() const
{
    return m_particleSystems;
}

const std::unordered_map<unsigned int, std::string>& AssetDictionary::getParticleEffects() const
{
    return m_particleEffects;
}

const std::unordered_map<unsigned int, std::string>& AssetDictionary::getParticleEmitters() const
{
    return m_particleEmitters;
}