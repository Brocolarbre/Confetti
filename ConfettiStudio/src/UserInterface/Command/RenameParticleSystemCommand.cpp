#include "RenameParticleSystemCommand.hpp"

RenameParticleSystemCommand::RenameParticleSystemCommand(ConfettiInstance& confettiInstance, unsigned int id, const std::string& name) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(id),
	m_name(name)
{

}

void RenameParticleSystemCommand::run()
{
	AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	std::string name = assetDictionary.getParticleSystemName(m_id);
	assetDictionary.setParticleSystemName(m_id, m_name);
	m_name = name;
}

void RenameParticleSystemCommand::revert()
{
	run();
}