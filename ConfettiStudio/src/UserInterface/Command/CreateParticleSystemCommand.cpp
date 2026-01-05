#include "CreateParticleSystemCommand.hpp"

CreateParticleSystemCommand::CreateParticleSystemCommand(ConfettiInstance& confettiInstance) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(0)
{

}

void CreateParticleSystemCommand::run()
{
	m_id = m_confettiInstance.getIdGenerators().system();
	m_confettiInstance.getParticleSimulation().getParticleRegistry().addParticleSystem(m_id, cft::ParticleSystem{});
	m_confettiInstance.getAssetDictionary().setParticleSystemName(m_id, "System");
}

void CreateParticleSystemCommand::revert()
{
	m_confettiInstance.getParticleSimulation().getParticleRegistry().removeParticleSystem(m_id);
	m_confettiInstance.getAssetDictionary().removeParticleSystemName(m_id);
}