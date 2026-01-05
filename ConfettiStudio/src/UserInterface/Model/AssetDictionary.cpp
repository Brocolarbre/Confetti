#include "AssetDictionary.hpp"

void AssetDictionary::setParticleSystemName(unsigned int id, const std::string& name)
{
    m_particleSystems[id] = name;
}

void AssetDictionary::setParticleEffectName(unsigned int id, const std::string& name)
{
    m_particleEffects[id] = name;
}

void AssetDictionary::setParticleEmitterName(unsigned int id, const std::string& name)
{
    m_particleEmitters[id] = name;
}

void AssetDictionary::removeParticleSystemName(unsigned int id)
{
    m_particleSystems.erase(id);
}

void AssetDictionary::removeParticleEffectName(unsigned int id)
{
    m_particleEffects.erase(id);
}

void AssetDictionary::removeParticleEmitterName(unsigned int id)
{
    m_particleEmitters.erase(id);
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