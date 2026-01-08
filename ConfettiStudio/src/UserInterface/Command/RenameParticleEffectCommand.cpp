#include "RenameParticleEffectCommand.hpp"

RenameParticleEffectCommand::RenameParticleEffectCommand(ConfettiInstance& confettiInstance, const std::string& name, const std::string& newName) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_name(name),
	m_newName(newName)
{

}

void RenameParticleEffectCommand::run()
{
	AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	unsigned int id = assetDictionary.getParticleEffectId(m_name);
	assetDictionary.removeParticleEffectId(m_name);
	assetDictionary.setParticleEffectId(m_newName, id);
	std::swap(m_name, m_newName);
}

void RenameParticleEffectCommand::revert()
{
	run();
}