#pragma once

#include "Model.hpp"

class AssetDictionary : public Model
{
private:
	std::unordered_map<std::string, unsigned int> m_particleSystems;
	std::unordered_map<std::string, unsigned int> m_particleEffects;
	std::unordered_map<std::string, unsigned int> m_particleEmitters;

public:
	void setParticleSystemId(const std::string& name, unsigned int id);
	void setParticleEffectId(const std::string& name, unsigned int id);
	void setParticleEmitterId(const std::string& name, unsigned int id);

	void removeParticleSystemId(const std::string& name);
	void removeParticleEffectId(const std::string& name);
	void removeParticleEmitterId(const std::string& name);

	unsigned int getParticleSystemId(const std::string& name) const;
	unsigned int getParticleEffectId(const std::string& name) const;
	unsigned int getParticleEmitterId(const std::string& name) const;

	std::string getParticleSystemName(unsigned int id) const;
	std::string getParticleEffectName(unsigned int id) const;
	std::string getParticleEmitterName(unsigned int id) const;

	const std::unordered_map<std::string, unsigned int>& getParticleSystems() const;
	const std::unordered_map<std::string, unsigned int>& getParticleEffects() const;
	const std::unordered_map<std::string, unsigned int>& getParticleEmitters() const;
};