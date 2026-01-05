#pragma once

#include <string>
#include <unordered_map>

class AssetDictionary
{
private:
	std::unordered_map<unsigned int, std::string> m_particleSystems;
	std::unordered_map<unsigned int, std::string> m_particleEffects;
	std::unordered_map<unsigned int, std::string> m_particleEmitters;

public:
	void setParticleSystemName(unsigned int id, const std::string& name);
	void setParticleEffectName(unsigned int id, const std::string& name);
	void setParticleEmitterName(unsigned int id, const std::string& name);

	void removeParticleSystemName(unsigned int id);
	void removeParticleEffectName(unsigned int id);
	void removeParticleEmitterName(unsigned int id);

	const std::string& getParticleSystemName(unsigned int id) const;
	const std::string& getParticleEffectName(unsigned int id) const;
	const std::string& getParticleEmitterName(unsigned int id) const;
};