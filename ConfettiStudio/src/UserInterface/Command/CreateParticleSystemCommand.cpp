#include "CreateParticleSystemCommand.hpp"

CreateParticleSystemCommand::CreateParticleSystemCommand(ConfettiInstance& confettiInstance, const std::string& name) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(0),
	m_name(name)
{

}

void CreateParticleSystemCommand::run()
{
	m_id = m_confettiInstance.getIdGenerators().system();
	m_confettiInstance.getParticleSimulation().getParticleRegistry().addParticleSystem(m_id, cft::ParticleSystem{});
	m_confettiInstance.getAssetDictionary().setParticleSystemId(m_name, m_id);
}

void CreateParticleSystemCommand::revert()
{
	m_confettiInstance.getParticleSimulation().getParticleRegistry().removeParticleSystem(m_id);
	m_confettiInstance.getAssetDictionary().removeParticleSystemId(m_name);
}