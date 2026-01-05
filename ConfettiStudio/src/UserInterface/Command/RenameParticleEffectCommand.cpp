#include "RenameParticleEffectCommand.hpp"

RenameParticleEffectCommand::RenameParticleEffectCommand(ConfettiInstance& confettiInstance, unsigned int id, const std::string& name) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(id),
	m_name(name)
{

}

void RenameParticleEffectCommand::run()
{
	AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	std::string name = assetDictionary.getParticleEffectName(m_id);
	assetDictionary.setParticleEffectName(m_id, m_name);
	m_name = name;
}

void RenameParticleEffectCommand::revert()
{
	run();
}