#include "CreateParticleEffectCommand.hpp"

CreateParticleEffectCommand::CreateParticleEffectCommand(ConfettiInstance& confettiInstance) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(0)
{

}

void CreateParticleEffectCommand::run()
{
	m_id = m_confettiInstance.getIdGenerators().effect();
	m_confettiInstance.getParticleSimulation().getParticleRegistry().addParticleEffect(m_id, cft::ParticleEffect{});
	m_confettiInstance.getAssetDictionary().setParticleEffectName(m_id, "Effect");
}

void CreateParticleEffectCommand::revert()
{
	m_confettiInstance.getParticleSimulation().getParticleRegistry().removeParticleEffect(m_id);
	m_confettiInstance.getAssetDictionary().removeParticleEffectName(m_id);
}