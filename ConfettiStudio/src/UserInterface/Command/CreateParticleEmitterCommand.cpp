#include "CreateParticleEmitterCommand.hpp"

CreateParticleEmitterCommand::CreateParticleEmitterCommand(ConfettiInstance& confettiInstance, const std::string& name) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(0),
	m_name(name)
{

}

void CreateParticleEmitterCommand::run()
{
	m_id = m_confettiInstance.getIdGenerators().emitter();
	m_confettiInstance.getParticleSimulation().getParticleRegistry().addParticleEmitter(m_id, cft::ParticleEmitter{});
	m_confettiInstance.getAssetDictionary().setParticleEmitterId(m_name, m_id);
}

void CreateParticleEmitterCommand::revert()
{
	m_confettiInstance.getParticleSimulation().getParticleRegistry().removeParticleEmitter(m_id);
	m_confettiInstance.getAssetDictionary().removeParticleEmitterId(m_name);
}