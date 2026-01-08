#include "RenameParticleEmitterCommand.hpp"

RenameParticleEmitterCommand::RenameParticleEmitterCommand(ConfettiInstance& confettiInstance, const std::string& name, const std::string& newName) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_name(name),
	m_newName(newName)
{

}

void RenameParticleEmitterCommand::run()
{
	AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	unsigned int id = assetDictionary.getParticleEmitterId(m_name);
	assetDictionary.removeParticleEmitterId(m_name);
	assetDictionary.setParticleEmitterId(m_newName, id);
	std::swap(m_name, m_newName);
}

void RenameParticleEmitterCommand::revert()
{
	run();
}