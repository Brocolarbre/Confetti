#include "RenameParticleSystemCommand.hpp"

RenameParticleSystemCommand::RenameParticleSystemCommand(ConfettiInstance& confettiInstance, const std::string& name, const std::string& newName) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_name(name),
	m_newName(newName)
{

}

void RenameParticleSystemCommand::run()
{
	AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	unsigned int id = assetDictionary.getParticleSystemId(m_name);
	assetDictionary.removeParticleSystemId(m_name);
	assetDictionary.setParticleSystemId(m_newName, id);
	std::swap(m_name, m_newName);
}

void RenameParticleSystemCommand::revert()
{
	run();
}