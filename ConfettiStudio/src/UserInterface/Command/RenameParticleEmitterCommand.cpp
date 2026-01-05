#include "RenameParticleEmitterCommand.hpp"

RenameParticleEmitterCommand::RenameParticleEmitterCommand(ConfettiInstance& confettiInstance, unsigned int id, const std::string& name) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(id),
	m_name(name)
{

}

void RenameParticleEmitterCommand::run()
{
	AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	std::string name = assetDictionary.getParticleEmitterName(m_id);
	assetDictionary.setParticleEmitterName(m_id, m_name);
	m_name = name;
}

void RenameParticleEmitterCommand::revert()
{
	run();
}