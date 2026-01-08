#include "CreateParticleEffectCommand.hpp"

CreateParticleEffectCommand::CreateParticleEffectCommand(ConfettiInstance& confettiInstance, const std::string& name) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(0),
	m_name(name)
{

}

void CreateParticleEffectCommand::run()
{
	m_id = m_confettiInstance.getIdGenerators().effect();
	m_confettiInstance.getParticleSimulation().getParticleRegistry().addParticleEffect(m_id, cft::ParticleEffect{});
	m_confettiInstance.getAssetDictionary().setParticleEffectId(m_name, m_id);
}

void CreateParticleEffectCommand::revert()
{
	m_confettiInstance.getParticleSimulation().getParticleRegistry().removeParticleEffect(m_id);
	m_confettiInstance.getAssetDictionary().removeParticleEffectId(m_name);
}